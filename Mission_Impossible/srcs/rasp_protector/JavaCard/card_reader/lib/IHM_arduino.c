#include "headers/IHM_arduino.h"

extern int serial_arduino;

int init_serial_communication() {
	serial_arduino = serialport_init("/dev/ttyACM0", 115200);
	if (serial_arduino < 0) return _ERROR_INIT_SERIAL_;
}

void show_message_to_user_arduino(char *msg) {
	serialport_write(serial_arduino, msg);
}

void get_code_from_user_arduino(char *code_dst) {
	int i, way_code=1;
	char buffer[10];

	bzero(buffer, sizeof(char)*10);

	do {
		serialport_read_until(serial_arduino, buffer, '\n', 1, 1000);

		if (buffer[0] != 0) {
			for(i=0; i<4; i++) {
				if (buffer[i] >= '0' && buffer[i] <= '9')
					code_dst[i] = buffer[i];
				else
					code_dst[i] = '0';
			}
			code_dst[4] = 0;
			way_code = 0;
		}
	} while(way_code);
}