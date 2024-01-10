# Linux
PCSC_CFLAGS := $(shell pkg-config --cflags libpcsclite)
LDFLAGS := $(shell pkg-config --libs libpcsclite)

# Mac OS X
# PCSC_CFLAGS := -framework PCSC

CFLAGS += $(PCSC_CFLAGS)
CC=gcc

# pour mac commentais IHM_arduino.o
OBJS= main.o                \
      interactWithReader.o  \
      interactWithCard.o    \
      IHM_computer.o        \
      serialCommunication.o \
      camDetected.o         \
      IHM_arduino.o
EXECNAME = badgeReader

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECNAME) -lpcsclite # for linux
# 	$(CC) $(CFLAGS) $(OBJS) -o $(EXECNAME)          # for MAC

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
interactWithReader.o: lib/interactWithReader.c lib/headers/interactWithReader.h
	$(CC) $(CFLAGS) -c lib/interactWithReader.c
interactWithCard.o: lib/interactWithCard.c lib/headers/interactWithCard.h
	$(CC) $(CFLAGS) -c lib/interactWithCard.c
IHM_computer.o: lib/IHM_computer.c lib/headers/IHM_computer.h
	$(CC) -c lib/IHM_computer.c
serialCommunication.o: lib/serialCommunication.c lib/headers/serialCommunication.h
	$(CC) -c lib/serialCommunication.c
# pour mac: commenter IHM_arduino.o
IHM_arduino.o: lib/IHM_arduino.c lib/headers/IHM_arduino.h
	$(CC) -c lib/IHM_arduino.c
camDetected.o: lib/camDetected.c lib/headers/camDetected.h
	$(CC) -c lib/camDetected.c

clean:
	rm -f $(OBJS) $(EXECNAME)

# Pour un usage pour terminal linux/mac:
#
#   dans main.c chnager :
#     #define ON_RASP 1
#   par
#     #define ON_RASP 0
#
#   commentez:
#     #include "lib/headers/IHM_arduino.h"
