
CPP=g++
RNG_FLAGS:=-Wno-unused-but-set-variable -Wno-unused-parameter -Wno-sign-compare
CPP_FLAGS:=-O3 -pedantic -Wall -Wextra ${RNG_FLAGS}

HASH_SRC:=lib/hash/hash.c
HASH_INCLUDE:=-I lib/hash -lcrypto

RNG_SRC:=lib/rng/rng.c
RNG_INCLUDE:=-I lib/rng

FFI_SRC:=src/ffi
FFI_INCLUDE:=-I src/ffi -lntl -lgmp -pthread

SRC:=src
INCLUDE:=-I src $(FFI_INCLUDE)
LIB:=$(HASH_INCLUDE) $(RNG_INCLUDE)

MAIN_RQC:=src/main_rqc.cpp
MAIN_KAT:=src/main_kat.c

RQC_OBJS:=ffi_field.o ffi_elt.o ffi_vec.o parsing.o q_polynomial.o gabidulin.o rqc.o kem.o
RQC_OBJS_VERBOSE:=ffi_field.o ffi_elt.o ffi_vec.o parsing.o q_polynomial.o gabidulin-verbose.o rqc-verbose.o kem-verbose.o
LIB_OBJS:=hash.o rng.o

BUILD:=bin/build
BIN:=bin



folders:
	@echo -e "\n### Creating build folders\n"
	mkdir -p $(BUILD)

hash.o: folders
	@echo -e "\n### Compiling $@ (wrapper around openssl SHA512 implementation)\n"
	$(CPP) $(CPP_FLAGS) -c $(HASH_SRC) $(HASH_INCLUDE) -o $(BUILD)/$@

rng.o: folders
	@echo -e "\n### Compiling NIST rng.o\n"
	$(CPP) $(CPP_FLAGS) -c $(RNG_SRC) $(RNG_INCLUDE) -o $(BUILD)/$@



ffi_%.o: $(FFI_SRC)/ffi_%.cpp | folders
	@echo -e "\n### Compiling $@\n"
	$(CPP) $(CPP_FLAGS) -c $< $(FFI_INCLUDE) $(LIB) -o $(BUILD)/$@

%.o: $(SRC)/%.cpp | folders
	@echo -e "\n### Compiling $@\n"
	$(CPP) $(CPP_FLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@

%-verbose.o: $(SRC)/%.cpp | folders
	@echo -e "\n### Compiling $@ (verbose mode)\n"
	$(CPP) $(CPP_FLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@



rqc192: $(RQC_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling RQC-192\n"
	$(CPP) $(CPP_FLAGS) $(MAIN_RQC) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

rqc192-kat: $(RQC_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling RQC-192 KAT\n"
	$(CPP) $(CPP_FLAGS) $(MAIN_KAT) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

rqc192-verbose: $(RQC_OBJS_VERBOSE) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling RQC-192 (verbose mode)\n"
	$(CPP) $(CPP_FLAGS) $(MAIN_RQC) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@



clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin

