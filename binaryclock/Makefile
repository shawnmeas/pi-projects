CC=gcc
CFLAGS=-Wall -std=c99

binaryclock: src/binaryclock.c
	$(CC) $(CFLAGS) -o bin/binaryclock src/binaryclock.c -lwiringPi
	
clean:
	rm -f bin/binaryclock

