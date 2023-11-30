# Linux
# PCSC_CFLAGS := $(shell pkg-config --cflags libpcsclite)
# LDFLAGS := $(shell pkg-config --libs libpcsclite)

# Mac OS X
PCSC_CFLAGS := -framework PCSC

CFLAGS += $(PCSC_CFLAGS)
CC=gcc
OBJS= main.o                \
      interactWithReader.o  \
      interactWithCard.o    \
      IHM_computer.o        \
      serialCommunication.o
EXECNAME = badgeReader

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECNAME)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
interactWithReader.o: lib/interactWithReader.c lib/headers/interactWithReader.h
	$(CC) $(CFLAGS) -c lib/interactWithReader.c
interactWithCard.o: lib/interactWithCard.c lib/headers/interactWithCard.h
	$(CC) $(CFLAGS) -c lib/interactWithCard.c
IHM_computer.o: lib/IHM_computer.c lib/headers/IHM_computer.h
	$(CC) $(CFLAGS) -c lib/IHM_computer.c
serialCommunication.o: lib/serialCommunication.c lib/headers/serialCommunication.h
	$(CC) $(CFLAGS) -c lib/serialCommunication.c

clean:
	rm -f $(OBJS) $(EXECNAME)