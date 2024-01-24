#ifndef __FILE_IO_H_
#define __FILE_IO_H_

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "key_tranform.h"
#include "parser.h"
#include "returns.h"

#define DEFAULT_FILE "out.keylog"

struct files_io_t {
	int fd_file_out;
	int fd_file_in;
	int fd_file_replay;
	int fd_file_export;
	int fd_file_export_txt;
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

#endif