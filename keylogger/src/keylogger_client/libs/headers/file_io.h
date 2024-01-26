/***********************************************************************
* FILENAME :  file_io.h
*
* DESCRIPTION :
*       Declaration des fonctions est des structure pour le fichier
*       file_io.c qui interagie avec les differents fichiers du projet
*
* AUTHOR :    Yanis GENY          START DATE :    26 Jan 2024
************************************************************************/

#ifndef __FILE_IO_H_
#define __FILE_IO_H_

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <strings.h>

#include "key_tranform.h"
#include "parser.h"
#include "returns.h"

#define DEFAULT_FILE "out.keylog"

#define MAX_STRING_SIZE 200

struct files_io_t {
	int fd_file_out;
	int fd_file_in;
	int fd_file_replay;
	int fd_file_export;
	int fd_file_export_txt;
	int fd_convert_speudokeylog;
	int fd_convert_keylog;
};

extern struct parser_t parser;

int  open_file_output(void);
void closed_files(void);
int  write_key_outfile(struct receive_key key);
int  open_replay_file(void);
int  open_export_file(void);
int  open_export_file_txt(void);
int  replay_saved_file(void);
int  write_export_file_to_text(void);
int  open_file_convert_speudokeylog(void);
int  open_files_convert_keylog(void);
int  convert_speudokeylog_to_keylog(void);
int  set_mod_from_compilation(int *mod, char *line_mod);
int  detect_mod_for_compilation(int *mod, char *char_mod);
int  read_line_from_convert_file(char *line);
int  extract_data_from_line(char *line, char *data);
int  extract_mod_from_mods(char *line, char *data);
int  open_input_file(void);
int  send_input_data_at_keylogger(void);

#endif