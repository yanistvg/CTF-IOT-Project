#include "headers/IHM_arduino.h"

int serial_arduino = 0;

/*
init_serial_communication permet d'ouvir la connection serie avec
une carte arduino connecte en /dev/ttyACM0 avec une vitesse de transmission
de 115200 baud

input :
	none

output:
	_SUCCESS_           -> si la conenction est etablie
	_ERROR_INIT_SERIAL_ -> si une erreur c'est produit lors de l'ouverture de la liaison
*/
int init_serial_communication() {
	serial_arduino = serialport_init("/dev/ttyACM0", 115200);
	if (serial_arduino < 0) return _ERROR_INIT_SERIAL_;
	return _SUCCESS_;
}

/*
show_message_to_user_arduino permet de transmettre un message a la carte
Arduino pour cette derniere puisse en faire l'affichage

input :
	char * -> message a transmettre a la carte arduino

output:
	none
*/
void show_message_to_user_arduino(char *msg) {
	serialport_write(serial_arduino, msg);
}

/*
get_code_from_user_arduino permet de recuperer un code saisie par un
utilisateur sur la carte arduino.

input :
	char * -> remplie le code de l'utilisateur

output:
	none
*/
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
					code_dst[index_code] = buffer[i] - 48;
					index_code++;
				}
				i++;
			}
		}

		if (index_code >= 4) wait_code = 0;

		bzero(buffer, sizeof(char)*10);

	} while(wait_code);

	code_dst[4] = 0;
}