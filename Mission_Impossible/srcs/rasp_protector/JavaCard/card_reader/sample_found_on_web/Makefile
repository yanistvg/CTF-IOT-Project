# Linux
# PCSC_CFLAGS := $(shell pkg-config --cflags libpcsclite)
# LDFLAGS := $(shell pkg-config --libs libpcsclite)

# Mac OS X
PCSC_CFLAGS := -framework PCSC

CFLAGS += $(PCSC_CFLAGS)

main: main.c

clean:
	rm -f main