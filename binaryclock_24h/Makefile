CC=gcc
CFLAGS=-Wall -std=c99

binaryclock_24h: src/binaryclock_24h.c
	$(CC) $(CFLAGS) -o bin/binaryclock_24h src/binaryclock_24h.c -lwiringPi
	
clean:
	rm -f bin/binaryclock_24h

