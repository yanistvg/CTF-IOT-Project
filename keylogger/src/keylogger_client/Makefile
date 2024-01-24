PROGNAME=keylogger-client
OBJS=main.o            \
     parser.o          \
     server_interact.o \
     key_tranform.o    \
     file_io.o

CC=gcc
FLAGS=-Wall

all: $(OBJS)
	$(CC) $(FLAGS) -o $(PROGNAME) $(OBJS)

main.o: main.c
	$(CC) $(FLAGS) -c main.c
parser.o: libs/parser.c libs/headers/parser.h
	$(CC) $(FLAGS) -c libs/parser.c
server_interact.o: libs/server_interact.c libs/headers/server_interact.h
	$(CC) $(FLAGS) -c libs/server_interact.c
key_tranform.o: libs/key_tranform.c libs/headers/key_tranform.h
	$(CC) $(FLAGS) -c libs/key_tranform.c
file_io.o: libs/file_io.c libs/headers/file_io.h
	$(CC) $(FLAGS) -c libs/file_io.c

clean:
	rm -f $(OBJS) $(PROGNAME)