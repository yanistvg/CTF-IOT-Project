#include "headers/file_io.h"

struct files_io_t files = {0, 0, 0, 0, 0};

/*
*  open_file_output permet d'ouvrir le fichier qui enregistre
*  les touches de l'utilisateur. Si dans les parametre de la
*  commande, il n'y a pas de fichier donne, un fichier sera creer
*  par defautl
*
*  input : none
*
*  output:
*     _ERROR_OPEN_OUT_FILE_ -> si le fichier n'a pa pu etre ouvert
*     _SUCCESS_             -> si pas d'erreur
*/
int open_file_output(void) {
	char filename[MAX_SIZE_FILE];

	// si le fichier est renseigner, l'ouvrir sinon ouvrir un fichier par defautl
	if ((parser.parser & PARSER_FLAG_OUTPUT) == PARSER_FLAG_OUTPUT)
		strcpy(filename, parser.output);
	else strcpy(filename, DEFAULT_FILE);

	files.fd_file_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (files.fd_file_out < 0) return _ERROR_OPEN_OUT_FILE_;

	return _SUCCESS_;
}

/*
*  closed_files permet de fermer les fichier in out qui sont
*  ouvert
*
*  input : none
*
*  output: none
*/
void closed_files(void) {
	if (files.fd_file_out        != 0) close(files.fd_file_out);
	if (files.fd_file_in         != 0) close(files.fd_file_in);
	if (files.fd_file_replay     != 0) close(files.fd_file_replay);
	if (files.fd_file_export     != 0) close(files.fd_file_export);
	if (files.fd_file_export_txt != 0) close(files.fd_file_export_txt);
}

/*
*  write_key_outfile permet d'ecrire dans le fichier de sortie
*  la touche intercepte au format lisible par le programme
*
*  input :
*    struct receive_key key -> touche intercepte
*
*  output:
*    _ERROR_FILE_NOT_OPEN_ -> si le fichier n'est pas ouvert
*    _ERROR_WRITE_FILE_    -> si une erreur est survenue lors de l'ecriture
*    _SUCCESS_             -> si pas d'erreur
*/
int write_key_outfile(struct receive_key key) {
	struct save_char_t key_save = {{0, 0}, 0, 0};

	if (files.fd_file_out <= 0) return _ERROR_FILE_NOT_OPEN_;

	tranforme_received_key(key, &key_save);
	if (write(files.fd_file_out, &key_save, sizeof(struct save_char_t)) < 0)
		return _ERROR_WRITE_FILE_;

	return _SUCCESS_;
}

/*
*  open_replay_file permet d'ouvrir le fichier de replay.
*
*  input : none
*
*  output:
*    _ERROR_OPEN_REPLAY_FILE_ -> si le fichier n'a pas etais ouvert
*    _SUCCESS_                -> si pas d'erreur
*/
int open_replay_file(void) {
	files.fd_file_replay = open(parser.replay, O_RDONLY);
	if (files.fd_file_replay < 0) return _ERROR_OPEN_REPLAY_FILE_;

	return _SUCCESS_;
}

/*
*  open_export_file permet d'ouvrir le fichier d'export
*
*  input : none
*
*  output:
*    _ERROR_OPEN_REPLAY_FILE_ -> si le fichier n'a pas etais ouvert
*    _SUCCESS_                -> si pas d'erreur
*/
int open_export_file(void) {
	files.fd_file_export = open(parser.exp, O_RDONLY);
	if (files.fd_file_export < 0) return _ERROR_OPEN_REPLAY_FILE_;

	return _SUCCESS_;
}

/*
*  open_export_file permet d'ouvrir le fichier d'export qui recevera
*  la sortie au format texte
*
*  input : none
*
*  output:
*    _ERROR_OPEN_REPLAY_FILE_ -> si le fichier n'a pas etais ouvert
*    _SUCCESS_                -> si pas d'erreur
*/
int open_export_file_txt(void) {
	char filename[MAX_SIZE_FILE];

	strcpy(filename, parser.exp);
	strcat(filename, ".txt");

	files.fd_file_export_txt = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (files.fd_file_export_txt < 0) return _ERROR_OPEN_OUT_FILE_;

	return _SUCCESS_;
}

/*
*  replay_saved_file permet de rejouer le fichier de replay
*
*  input : none
*
*  output:
*     _ERROR_FILE_NOT_OPEN_ -> si le ficier n'est pas ouvert
*     _ERROR_READING_FILE_  -> en cas d'erreur de lecture
*     _SUCCESS_             -> si pas d'erreur
*/
int replay_saved_file(void) {
	struct save_char_t key;
	struct receive_key show_key;
	int                running = 1;
	int                n;
	struct timeval     old_timestamp = {0, 0};
	int                time_to_sleep;

	if (files.fd_file_replay <= 0) return _ERROR_FILE_NOT_OPEN_;

	while (running) {
		n = read(files.fd_file_replay, &key, sizeof(struct save_char_t));
		if (n < 0) return _ERROR_READING_FILE_; // si erreur de lecture
		if (n < sizeof(struct save_char_t)) return _SUCCESS_; // si fin du fichier

		 // marquer un temp de pause
		if (old_timestamp.tv_sec != 0) {
			time_to_sleep  = (key.timestamp.tv_sec - old_timestamp.tv_sec) * 1000000;
			time_to_sleep += (key.timestamp.tv_usec - old_timestamp.tv_usec);
			usleep(time_to_sleep);
		}

		tranforme_received_key_to_key(&show_key, key);
		show_key_on_terminal(show_key, 0);
		old_timestamp.tv_sec  = key.timestamp.tv_sec;
		old_timestamp.tv_usec = key.timestamp.tv_usec;
	}

	return _SUCCESS_;
}

/*
*  write_export_file_to_text permet de lire le fichier de sauvegarde des touches
*  affin d'exporter les touche dans un fichier au format texte
*
*  input : none
*
*  output:
*    _ERROR_FILE_NOT_OPEN_ -> si un des fichier n'est pas ouvert
*    _SUCCESS_             -> si pas d'erreur
*/
int write_export_file_to_text(void) {
	int n;
	int running=1;
	struct save_char_t key;
	struct receive_key show_key;

	if (files.fd_file_export     <= 0) return _ERROR_FILE_NOT_OPEN_;
	if (files.fd_file_export_txt <= 0) return _ERROR_FILE_NOT_OPEN_;

	while (running) {
		n = read(files.fd_file_export, &key, sizeof(struct save_char_t));
		if (n < 0) return _ERROR_READING_FILE_; // si erreur de lecture
		if (n < sizeof(struct save_char_t)) return _SUCCESS_; // si fin du fichier

		tranforme_received_key_to_key(&show_key, key);
		show_key_on_terminal(show_key, files.fd_file_export_txt);
	}
	return _SUCCESS_;
}