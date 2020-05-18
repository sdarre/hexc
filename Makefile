all: build

build:
	gcc hexc.c -o hexc

install:
	mv hexc /usr/local/bin

uninstall:
	rm /usr/local/bin/hexc

clean:
	rm hexc
