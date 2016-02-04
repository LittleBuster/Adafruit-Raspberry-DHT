CC=g++
CXXFLAGS=-I. -pedantic -Wall -O2 -fPIC -std=c++11
LDFLAGS=-lrt

all: libdht

libdht: piio.o dht22.o
	$(CC) piio.o dht22.o -shared -o libdht22.so $(CXXFLAGS) $(LDFLAGS)

piio.o: piio.cpp
	$(CC) -c piio.cpp $(CXXFLAGS) $(LDFLAGS)

dht22.o: dht22.cpp
	$(CC) -c dht22.cpp $(CXXFLAGS) $(LDFLAGS)

install:
	cp libdht22.so /usr/lib/
	cp dht22.h /usr/include/

remove:
	rm /usr/lib/libdht22.so
	rm /usr/include/dht22.h

clean:
	rm -rf *.o *.so
