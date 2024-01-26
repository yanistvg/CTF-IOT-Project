/***********************************************************************
* FILENAME :  file_io.c
*
* DESCRIPTION :
*       Declaration des fonctions qui permettent l'interraction avec les
*       fichier pour le projet, comme les fichiers de sauvegarde des touches
*       , d'inportation vers le keylogger, et la compilation du speudokeylog
*
* AUTHOR :    Yanis GENY          START DATE :    26 Jan 2024
************************************************************************/

#include "headers/file_io.h"

struct files_io_t files = {0, 0, 0, 0, 0, 0, 0};

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
	if (files.fd_file_out             != 0) close(files.fd_file_out);
	if (files.fd_file_in              != 0) close(files.fd_file_in);
	if (files.fd_file_replay          != 0) close(files.fd_file_replay);
	if (files.fd_file_export          != 0) close(files.fd_file_export);
	if (files.fd_file_export_txt      != 0) close(files.fd_file_export_txt);
	if (files.fd_convert_speudokeylog != 0) close(files.fd_convert_speudokeylog);
	if (files.fd_convert_keylog       != 0) close(files.fd_convert_keylog);
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

/*
*  open_file_convert_speudokeylog permet d'ouvrire le fichier ecrit en speudokeylog
*
*  input : none
*
*  output:
*     _ERROR_OPEN_CONVERT_FILE_ -> en cas d'erreur d'ouverture du fichier
*     _SUCCESS_                 -> si pas d'erreur
*/
int open_file_convert_speudokeylog(void) {
	files.fd_convert_speudokeylog = open(parser.convert, O_RDONLY);
	if (files.fd_convert_speudokeylog < 0) return _ERROR_OPEN_CONVERT_FILE_;

	return _SUCCESS_;
}

/*
*  open_file_convert_speudokeylog permet d'ouvrire le fichier qui recevera
*  le resultat du speudokeylog en keylog
*
*  input : none
*
*  output:
*     _ERROR_OPEN_CONVERT_FILE_ -> en cas d'erreur d'ouverture du fichier
*     _SUCCESS_                 -> si pas d'erreur
*/
int open_files_convert_keylog(void) {
	char filename[MAX_SIZE_FILE];

	strcpy(filename, parser.convert);
	strcat(filename, ".keylog");

	files.fd_convert_keylog = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (files.fd_convert_keylog < 0) return _ERROR_OPEN_CONVERT_FILE_;

	return _SUCCESS_;
}

/*
*  convert_speudokeylog_to_keylog permet de faire la compilation du speudokeylog
*  en keylog
*
*  input : none
*
*  output:
*    int       -> le numero de la ligne qui contient une erreur
*    _SUCCESS_ -> si pas d'erreur
*/
int convert_speudokeylog_to_keylog(void) {
	char               line[MAX_STRING_SIZE];
	char               caractere[MAX_STRING_SIZE];
	char               interval[MAX_STRING_SIZE];
	char               mods[MAX_STRING_SIZE];
	struct save_char_t keylog = {{1, 0}, 0, 0};
	int                func_ret;
	int                error_gestion;
	int                i=1;

	if (files.fd_convert_speudokeylog <= 0) return _ERROR_FILE_NOT_OPEN_;
	if (files.fd_convert_keylog       <= 0) return _ERROR_FILE_NOT_OPEN_;

	while ((func_ret = read_line_from_convert_file(line)) == _SUCCESS_) {
		// dans line, extraire le caractere, le temps d'attente avant, et les mods
		error_gestion = extract_data_from_line(line, caractere); // extraction du caractere
		if (error_gestion != _SUCCESS_) return i;
		error_gestion = extract_data_from_line(line, interval); // extraction du temps d'attente
		if (error_gestion != _SUCCESS_) return i;
		error_gestion = extract_data_from_line(line, mods); // extraction des modes
		if (error_gestion != _SUCCESS_) return i;

		// trouver la keyvalue liee au caractere
		if (found_value_from_key_speudokeylog(caractere, &error_gestion) != _SUCCESS_) return i;
		keylog.ch = (char)(error_gestion);

		// changer le temps
		keylog.timestamp.tv_sec += atoi(interval) / 1000000;
		keylog.timestamp.tv_usec += atoi(interval) % 1000000;

		// trouver tous les modes
		keylog.mod = 0;
		if (set_mod_from_compilation(&keylog.mod, mods) != _SUCCESS_) return i;

		// sauvegarder dans le fichier de sortie la structure
		write(files.fd_convert_keylog, &keylog, sizeof(struct save_char_t));

		i++;
	}

	return _SUCCESS_;
}

/*
*  set_mod_from_compilation permet d'ajouter les mode a un int en fonction
*  d'une chaine de caractere qui contient les different mod separe par une
*  virgule
*
*  input :
*    int *mod       -> entier a remplir des modes
*    char *line_mod -> liste des mod en text
*
*  output:
*    _MOD_NOT_FOUND_     -> si le mod n'existe pas
*    _CANT_EXTRACT_DATA_ -> si mauvais formatage des modes
*    _SUCCESS_           -> si pas d'erreur
*/
int set_mod_from_compilation(int *mod, char *line_mod) {
	char char_mod[MAX_STRING_SIZE];
	int func_ret;

	if (line_mod[0] == 0) return _SUCCESS_;

	while ((func_ret = extract_mod_from_mods(line_mod, char_mod)) == _SUCCESS_) {
		if (detect_mod_for_compilation(mod, char_mod) != _SUCCESS_) return _MOD_NOT_FOUND_;
	}
	if (func_ret == _LAST_DATA_) {
		if (detect_mod_for_compilation(mod, char_mod) != _SUCCESS_) return _MOD_NOT_FOUND_;
	}
	if (func_ret == _CANT_EXTRACT_DATA_) return _CANT_EXTRACT_DATA_;

	return _SUCCESS_;
}

/*
*  detect_mod_for_compilation permet d'appliquer pour un mode le masque
*  associe a l'entier en parametre
*
*  input :
*    int *mod       -> entier a remplir des modes
*    char *char_mod -> mod en text
*
*  output:
*    _MOD_NOT_FOUND_ -> si le mode n'est pas reconnue
*    _SUCCESS_       -> si pas d'erreur
*/
int detect_mod_for_compilation(int *mod, char *char_mod) {
	if (!strcmp(char_mod, "LEFT_CTRL")) { *mod |= 0x01; return _SUCCESS_; }
	if (!strcmp(char_mod, "LEFT_SHIFT")) { *mod |= 0x02; return _SUCCESS_; }
	if (!strcmp(char_mod, "ALT")) { *mod |= 0x04; return _SUCCESS_; }
	if (!strcmp(char_mod, "LEFT_CMD")) { *mod |= 0x08; return _SUCCESS_; }
	if (!strcmp(char_mod, "RIGHT_CTRL")) { *mod |= 0x10; return _SUCCESS_; }
	if (!strcmp(char_mod, "RIGHT_SHIFT")) { *mod |= 0x20; return _SUCCESS_; }
	if (!strcmp(char_mod, "ALT_GR")) { *mod |= 0x40; return _SUCCESS_; }
	if (!strcmp(char_mod, "RIGHT_CMD")) { *mod |= 0x80; return _SUCCESS_; }
	return _MOD_NOT_FOUND_;
}

/*
*  read_line_from_convert_file permet d'extraire une ligne du fichier
*  speudokeylog. Une ligne se terminant par \n
*
*  input :
*    char *line -> destination de la ligne lue
*
*  output:
*    _ERROR_READING_FILE_ -> en cas d'erreur de lecture
*    _END_FILE_           -> si le fichier est entierement lue
*    _SUCCESS_            -> si pas d'erreur
*/
int read_line_from_convert_file(char *line) {
	int  i=0;
	int  n;
	char c;

	bzero(line, sizeof(char)*MAX_STRING_SIZE);

	while((n = read(files.fd_convert_speudokeylog, &c, 1)) > 0) {
		line[i++] = c;
		if (c == '\n') return _SUCCESS_;
	}

	if (n == 0) return _END_FILE_;
	if (n < 0 ) return _ERROR_READING_FILE_;

	return _SUCCESS_;
}

/*
*  extract_data_from_line permet d'extraire une donne dans une ligne
*  delimite par :
*
*  input :
*    char *line -> ligne d'on t'il faut extraire la donne
*    char *data -> destination de la donne
*
*  output:
*    _CANT_EXTRACT_DATA_ -> si la donne n'a pas etais extraite
*    _SUCCESS_           -> si pas d'erreur
*/
int extract_data_from_line(char *line, char *data) {
	int i=0;
	int y=0;

	while (line[i] != ':' && line[i] != '\n' && line[i] != 0) {
		data[i] = line[i];
		i++;
	}
	data[i] = 0;

	if (line[i] == '\n') {
		bzero(line, sizeof(char)*MAX_STRING_SIZE);
		return _SUCCESS_;
	}

	if (line[i] == ':') {
		while(line[++i] != 0)
			line[y++] = line[i];
		line[y] = 0;
		return _SUCCESS_;
	}

	return _CANT_EXTRACT_DATA_;
}

/*
*  extract_mod_from_mods permet d'extraire une donne separer
*  par une virgule
*
*  input :
*    char *line -> ligne d'on t'il faut extraire la donne
*    char *data -> destination de la donne
*
*  output:
*    _CANT_EXTRACT_DATA_ -> si la donne n'a pas etais extraite
*    _LAST_DATA_         -> si c'est la derniere donne qui est dans la ligne
*    _SUCCESS_           -> si pas d'erreur
*/
int extract_mod_from_mods(char *line, char *data) {
	int i=0;
	int y=0;

	while (line[i] != ',' && line[i] != '\n' && line[i] != 0) {
		data[i] = line[i];
		i++;
	}
	data[i] = 0;

	if (line[i] == '\n') {
		bzero(line, sizeof(char)*MAX_STRING_SIZE);
		return _SUCCESS_;
	}

	if (line[i] == ',') {
		while(line[++i] != 0)
			line[y++] = line[i];
		line[y] = 0;
		return _SUCCESS_;
	}

	if (line[i] == 0) return _LAST_DATA_;

	return _CANT_EXTRACT_DATA_;
}

/*
*  open_input_file permet d'ouvir le fichier d'input
*
*  input : none
*
*  output:
*    _ERROR_OPEN_INPUT_FILE_ -> si le fichier n'est pas ouvert
*    _SUCCESS_               -> si pas d'erreur
*/
int open_input_file(void) {
	files.fd_file_in = open(parser.input, O_RDONLY);
	if (files.fd_file_in < 0) return _ERROR_OPEN_INPUT_FILE_;

	return _SUCCESS_;
}

/*
*  send_input_data_at_keylogger permet de lire le fichier input
*  et de transmettre les touche au serveyr keylogger en respoectant
*  les delay definie
*
*  input : none
*
*  output:
*    _ERROR_FILE_NOT_OPEN_ -> si le fichier input n'est pas ouvert
*    _ERROR_READING_FILE_  -> en cas d'erreur de lecture du fichier
*    _ERROR_WRITE_SRV_KEY_ -> en cas d'erreur lors de l'envoie au serveur
*    _SUCCESS_             -> si pas d'erreur
*/
int send_input_data_at_keylogger(void) {
	struct save_char_t key_in;
	struct receive_key key;
	int                n;
	int                running=1;
	struct timeval     old_timestamp = {0, 0};
	int                time_to_sleep;

	if (files.fd_file_in <= 0) return _ERROR_FILE_NOT_OPEN_;

	while (running) {
		n = read(files.fd_file_in, &key_in, sizeof(struct save_char_t));
		if (n < 0) return _ERROR_READING_FILE_; // si erreur de lecture
		if (n < sizeof(struct save_char_t)) return _SUCCESS_; // si fin du fichier

		// marquer un temp de pause
		if (old_timestamp.tv_sec != 0) {
			time_to_sleep  = (key_in.timestamp.tv_sec - old_timestamp.tv_sec) * 1000000;
			time_to_sleep += (key_in.timestamp.tv_usec - old_timestamp.tv_usec);
			usleep(time_to_sleep);
		}

		// changement du format de la touche pour la transmettre
		tranforme_received_key_to_key(&key, key_in);
		// envoie de la touche
		if (send_key(key) != _SUCCESS_)
			return _ERROR_WRITE_SRV_KEY_;
		old_timestamp.tv_sec  = key_in.timestamp.tv_sec;
		old_timestamp.tv_usec = key_in.timestamp.tv_usec;
	}
	return _SUCCESS_;
}