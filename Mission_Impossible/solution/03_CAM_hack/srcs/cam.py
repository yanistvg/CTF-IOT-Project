import socket
import time

HOST = "0.0.0.0"
PORT = 8081

HTTP_HEADER  = b""
HTTP_HEADER += b"HTTP/1.1 200 OK\r\n"
HTTP_HEADER += b"Connection: Keep-Alive\r\n"
HTTP_HEADER += b"Transfer-Encoding: chunked\r\n"
HTTP_HEADER += b"Content-Type: multipart/x-mixed-replace; boundary=BoundaryString\r\n"
HTTP_HEADER += b"Date: Sun, 12 Nov 2023 01:47:51 GMT\r\n"
HTTP_HEADER += b"\r\n"

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
serversocket.bind((HOST, PORT))
serversocket.listen(5)

print(f"Server UP at {HOST}:{PORT}")

try:
	while True:
		(clientsocket, address) = serversocket.accept()

		try:
			with clientsocket:
				print(f"Connection de {address}")
				buff = clientsocket.recv(1024)
				message = buff.decode('utf-8')
				clientsocket.send(HTTP_HEADER)
				time.sleep(0.01)
				while True:
					with open("payload.bin", "rb") as payload:
						while msg := payload.read(1000):
							clientsocket.send(msg)
					time.sleep(1)
		except ConnectionResetError:
			pass
		except BrokenPipeError:
			pass
		
		clientsocket.close()
except KeyboardInterrupt:
	serversocket.close()
	print(f"\rServer DOWN")
