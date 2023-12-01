#include "headers/IHM_arduino.h"

int serial_arduino = 0;

int init_serial_communication() {
	serial_arduino = serialport_init("/dev/ttyACM0", 115200);
	if (serial_arduino < 0) return _ERROR_INIT_SERIAL_;
}

void show_message_to_user_arduino(char *msg) {
	serialport_write(serial_arduino, msg);
}

void get_code_from_user_arduino(char *code_dst) {
	int i, wait_code=1;
	char buffer[10];
	int index_code = 0;

	bzero(buffer, sizeof(char)*10);

	do {
		serialport_read_until(serial_arduino, buffer, '\n', 1, 1000);

		if (buffer[0] != 0) {
			i=0;

			while(buffer[i] != 0 && index_code < 4) {
				if (buffer[i] >= '0' && buffer[i] <= '9') {
					code_dst[index_code] = buffer[i];
					index_code++;
				}
				i++;
			}
		}

		if (index_code >= 4) wait_code = 0;

		bzero(buffer, sizeof(char)*10);

	} while(wait_code);
}