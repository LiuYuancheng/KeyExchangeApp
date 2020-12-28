CFLAGS:=-I../../../lib
LFLAGS:=-lcrypto -L../../..  -lpqch

all: test_correctness.c test_key_size.c  ../rsa_kem.c ../rsa_kem.h
	clang++ -o test_correctness  test_correctness.c  ../rsa_kem.c $(CFLAGS)  $(LFLAGS)
	clang++ -o test_key_size test_key_size.c ../rsa_kem.c $(CFLAGS)  $(LFLAGS)
	clang++ -o test_perf test_perf.c format_helper.c  ../rsa_kem.c $(CFLAGS)  $(LFLAGS)

clean:
	rm -f test_correctness
	rm -f test_key_size
	rm -f test_perf
