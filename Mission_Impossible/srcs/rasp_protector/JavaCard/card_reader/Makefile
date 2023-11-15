# Linux
# PCSC_CFLAGS := $(shell pkg-config --cflags libpcsclite)
# LDFLAGS := $(shell pkg-config --libs libpcsclite)

# Mac OS X
PCSC_CFLAGS := -framework PCSC

CFLAGS += $(PCSC_CFLAGS)
CC=gcc
OBJS= main.o               \
      interactWithReader.o
EXECNAME = badgeReader

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECNAME)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
interactWithReader.o: lib/interactWithReader.c lib/headers/interactWithReader.h
	$(CC) $(CFLAGS) -c lib/interactWithReader.c

clean:
	rm -f $(OBJS) $(EXECNAME)