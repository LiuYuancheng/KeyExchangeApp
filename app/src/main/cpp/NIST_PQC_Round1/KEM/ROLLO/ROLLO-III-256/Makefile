
CC=g++
CFLAGS:=-O2 -pedantic -Wno-vla

HASH_SRC:=lib/hash/hash.c
HASH_INCLUDE:=-I lib/hash -lcrypto

RNG_SRC:=lib/rng/rng.c
RNG_INCLUDE:=-I lib/rng

FFI_SRC:=src/ffi
FFI_INCLUDE:=-I src/ffi -lntl -lgmp

SRC:=src
INCLUDE:=-I src $(FFI_INCLUDE)
LIB:=$(HASH_INCLUDE) $(RNG_INCLUDE)

MAIN_ROLLO:=src/main_rollo.cpp
MAIN_KAT:=src/main_kat.c

ROLLO_OBJS:=ffi_field.o ffi_elt.o ffi_vec.o parsing.o rsr_algorithm.o kem.o 
ROLLO_OBJS_VERBOSE:=ffi_field.o ffi_elt.o ffi_vec.o parsing.o rsr_algorithm-verbose.o kem-verbose.o
LIB_OBJS:=hash.o rng.o

BUILD:=bin/build
BIN:=bin



folders:
	@echo -e "\n### Creating build folders\n"
	mkdir -p $(BUILD)

hash.o: folders
	@echo -e "\n### Compiling $@ (wrapper around openssl SHA512 implementation)\n"
	$(CC) $(CFLAGS) -c $(HASH_SRC) $(HASH_INCLUDE) -o $(BUILD)/$@

rng.o: folders
	@echo -e "\n### Compiling NIST rng.o\n"
	$(CC) $(CFLAGS) -c $(RNG_SRC) $(RNG_INCLUDE) -o $(BUILD)/$@



ffi_%.o: $(FFI_SRC)/ffi_%.cpp | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(FFI_INCLUDE) $(LIB) -o $(BUILD)/$@

%.o: $(SRC)/%.cpp | folders
	@echo -e "\n### Compiling $@\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@

%-verbose.o: $(SRC)/%.cpp | folders
	@echo -e "\n### Compiling $@ (verbose mode)\n"
	$(CC) $(CFLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@



rollo-III-256: $(ROLLO_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling ROLLO-III-256\n"
	$(CC) $(CFLAGS) $(MAIN_ROLLO) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

rollo-III-256-kat: $(ROLLO_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling ROLLO-III-256 KAT\n"
	$(CC) $(CFLAGS) $(MAIN_KAT) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

rollo-III-256-verbose: $(ROLLO_OBJS_VERBOSE) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling ROLLO-III-256 (verbose mode)\n"
	$(CC) $(CFLAGS) $(MAIN_ROLLO) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@



clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin

