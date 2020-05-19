CC = gcc
CFLAGS = -std=c99

all: build

build:
	$(CC) hexc.c $(CFLAGS) -o hexc

install:
	mkdir -p /usr/local/bin
	mv hexc /usr/local/bin

uninstall:
	rm /usr/local/bin/hexc

clean:
	rm -f hexc