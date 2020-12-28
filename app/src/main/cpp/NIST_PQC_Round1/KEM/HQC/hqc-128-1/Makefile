
CPP=g++
RNG_FLAGS:=-Wno-unused-but-set-variable -Wno-unused-parameter -Wno-sign-compare
CPP_FLAGS:=-O3 -Wall -Wextra ${RNG_FLAGS}

HASH_SRC:=lib/hash/hash.c
HASH_INCLUDE:=-I lib/hash -lcrypto

RNG_SRC:=lib/rng/rng.c
RNG_INCLUDE:=-I lib/rng

SRC:=src/
INCLUDE:=-I src -lntl -lgf2x -lgmp -pthread
LIB:=$(HASH_INCLUDE) $(RNG_INCLUDE)

MAIN_HQC:=src/main_hqc.cpp
MAIN_KAT:=src/main_kat.c

HQC_OBJS:=vector.o bch.o repetition.o tensor.o parsing.o hqc.o kem.o gf2x.o
HQC_OBJS_VERBOSE:=vector.o repetition.o bch-verbose.o tensor-verbose.o parsing.o hqc-verbose.o kem-verbose.o gf2x.o
LIB_OBJS:= hash.o rng.o 

BIN:=bin
BUILD:=bin/build


folders:
	@echo -e "\n### Creating folders\n"
	mkdir -p $(BUILD)

hash.o: folders
	@echo -e "\n### Compiling $@ (wrapper around openssl SHA512 implementation)\n"
	$(CPP) $(CPP_FLAGS) -c $(HASH_SRC) $(HASH_INCLUDE) -o $(BUILD)/$@

rng.o: folders
	@echo -e "\n### Compiling NIST rng.o\n"
	$(CPP) $(CPP_FLAGS) -c $(RNG_SRC) $(RNG_INCLUDE) -o $(BUILD)/$@

%.o: $(SRC)/%.cpp | folders
	@echo -e "\n### Compiling $@\n"
	$(CPP) $(CPP_FLAGS) -c $< $(INCLUDE) $(LIB) -o $(BUILD)/$@

%-verbose.o: $(SRC)/%.cpp | folders
	@echo -e "\n### Compiling $@ (verbose mode)\n"
	$(CPP) $(CPP_FLAGS) -c $< $(INCLUDE) $(LIB) -D VERBOSE -o $(BUILD)/$@

hqc-128-1: $(HQC_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling HQC-128-1\n"
	$(CPP) $(CPP_FLAGS) $(MAIN_HQC) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

hqc-128-1-kat: $(HQC_OBJS) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling HQC-128-1 KAT\n"
	$(CPP) $(CPP_FLAGS) $(MAIN_KAT) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -o $(BIN)/$@

hqc-128-1-verbose: $(HQC_OBJS_VERBOSE) $(LIB_OBJS) | folders
	@echo -e "\n### Compiling HQC-128-1 (verbose mode)\n"
	$(CPP) $(CPP_FLAGS) $(MAIN_HQC) $(addprefix $(BUILD)/, $^) $(INCLUDE) $(LIB) -D VERBOSE -o $(BIN)/$@


clean:
	rm -f PQCkemKAT_*
	rm -f vgcore.*
	rm -rf ./bin