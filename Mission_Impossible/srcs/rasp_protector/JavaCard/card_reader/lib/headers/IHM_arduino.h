#ifndef __IHM_ARDUINO_H__

#include "serialCommunication.h"
#include "return_code.h"

int serial_arduino = 0; // file descriptor to communicat with arduino in serial UART

int init_serial_communication();
void show_message_to_user_arduino(char *msg);

#endif