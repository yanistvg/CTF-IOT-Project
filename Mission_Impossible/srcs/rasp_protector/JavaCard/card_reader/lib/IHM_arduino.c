#include "headers/IHM_arduino.h"

int init_serial_communication() {
	serial_arduino = serialport_init("/dev/ttyUSB0", 115200);
	if (serial_arduino < 0) return _ERROR_INIT_SERIAL_;
}

void show_message_to_user_arduino(char *msg) {
	serialport_write(serial_arduino, msg);
}