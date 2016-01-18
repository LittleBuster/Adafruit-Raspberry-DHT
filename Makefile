CC=gcc
CFLAGS=-I. -pedantic -Wall -O2 -fPIC -std=gnu99
LDFLAGS=-lrt

all: libdht

libdht: piio.o dht22.o
	$(CC) piio.o dht22.o -shared -o libdht22.so $(CFLAGS) $(LDFLAGS)

piio.o: piio.c
	$(CC) -c piio.c $(CFLAGS) $(LDFLAGS)

dht22.o: dht22.c
	$(CC) -c dht22.c $(CFLAGS) $(LDFLAGS)

install:
	sudo cp libdht22.so /usr/lib/
	sudo cp dht22.h /usr/include/

remove:
	rm /usr/lib/libdht22.so
	rm /usr/include/dht22.h

clean:
	rm -rf *.o *.so
