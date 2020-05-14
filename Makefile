all:
	gcc hexc.c -lm -o hexc
	sudo mv hexc /usr/local/bin

clean:
	sudo rm -f /usr/local/bin/hexc