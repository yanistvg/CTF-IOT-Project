PROGNAME=keylogger-client
OBJS=main.o            \
     parser.o          \
     server_interact.o

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

clean:
	rm -f $(OBJS) $(PROGNAME)