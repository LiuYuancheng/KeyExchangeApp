
# BIKE reference and optimized implementations assume that OpenSSL and NTL libraries are available in the platform.

# To compile this code for NIST KAT routine use: make bike-nist-kat
# To compile this code for demo tests use: make bike-demo-test

# TO EDIT PARAMETERS AND SELECT THE BIKE VARIANT: please edit defs.h file in the indicated sections.

# The file measurements.h controls how the cycles are counted. Note that #define REPEAT is initially set to 100, 
# which means that every keygen, encaps and decaps is repeated 100 times and the number of cycles is averaged.

# Verbose levels: 0, 1, 2 or 3
VERBOSE=0

CC:=g++
CFLAGS:=-m64 -O3 

SRC:=*.c ntl.cpp FromNIST/rng.c
#INCLUDE:=-I. -I$(OpenSSL)/include -L$(OpenSSL)/lib -std=c++11 -lcrypto -lssl -lm -ldl -lpthread -lntl -lgmp -lgf2x
INCLUDE:=-I. -I/usr/local/include   -std=c++11 -lcrypto -lssl -lm -ldl -lpthread -lntl -lgmp  -L/usr/local/lib -lgf2x

all: bike-nist-kat

bike-alice: $(SRC) *.h  Alice.c
	$(CC) $(CFLAGS) Alice.c   $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 -o $@

bike-bob: $(SRC) *.h  /Bob.c
	$(CC) $(CFLAGS) Bob.c   $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 -o $@

bike-demo-test: $(SRC) *.h tests/test.c
	$(CC) $(CFLAGS) tests/test.c $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 -o $@

bike-nist-kat: $(SRC) *.h FromNIST/*.h FromNIST/PQCgenKAT_kem.c
	$(CC) $(CFLAGS) FromNIST/PQCgenKAT_kem.c $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 -o $@

bike-lib: $(SRC) *.h
	$(CC) $(CFLAGS) -c  -fPIC $(SRC) $(INCLUDE) -DVERBOSE=$(VERBOSE) -DNIST_RAND=1 
	$(CC) -shared -fPIC $(INCLUDE) -o libbike.so *.o
install:
	mkdir -p /usr/local/include/bike
	cp *.h /usr/local/include/bike
	cp libbike.so /usr/local/lib
clean:
#	rm -f PQCkemKAT_*
	rm -f bike*

