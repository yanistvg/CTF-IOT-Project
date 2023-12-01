#ifndef __IHM_ARDUINO_H__

#include "serialCommunication.h"
#include "return_code.h"
#include <strings.h>

extern int serial_arduino; // file descriptor to communicat with arduino in serial UART

int init_serial_communication();
void show_message_to_user_arduino(char *msg);
void get_code_from_user_arduino(char *code_dst);

#endif