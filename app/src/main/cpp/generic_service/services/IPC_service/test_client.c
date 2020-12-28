/*
 * test_client1.c
 *
 *  Created on: 23 Apr 2020
 *      Author: yiwen
 */
#include <inttypes.h>
#include <openssl/bio.h>
#include <string.h>

#include <libipc/ipc_shm_generic.h>

int main(int argc, char *argv[]) {
	int repeats;

	if (argc < 2) {
		repeats = 1;
	} else {
		repeats = atoi(argv[1]);
	}
	/*	set shared memory*/
	struct IPC_shm *shm_c2s, *shm_s2c;

	if (IPC_shm_init(&shm_c2s, 0x001A, 0) || IPC_shm_init(&shm_s2c, 0x001B, 0)) {
		printf("IPC Shared memory configuration error!\n");

		return -1;
	}

	uint8_t ss[1024];
	size_t olen = 0;

	memset(ss, 0, sizeof(ss));

	for (int n = 0; n < repeats; n++) {
		printf("########## ID = %d #########\n", n);
		if (0 == IPC_shm_write(shm_c2s, 0, 0)) {
			if (0 == IPC_shm_read(shm_s2c, ss, &olen)) {
				printf("Client Read ss:\n");
				BIO_dump_fp(stdout, ss, olen);
			}
		}

	}
}

