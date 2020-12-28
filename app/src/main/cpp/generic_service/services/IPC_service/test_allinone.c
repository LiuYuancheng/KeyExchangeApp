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

int main(int argc, char **argv)
{
	int nRepeats = atoi(argv[1]);
	/*	set shared memory*/
	struct IPC_shm *shm_c2s_cli, *shm_s2c_cli, *shm_c2s_ser, *shm_s2c_ser;

	if (IPC_shm_init(&shm_c2s_cli, 0x001A, 0) || IPC_shm_init(&shm_s2c_cli, 0x001B, 0))
	{
		printf("IPC Shared memory configuration error!\n");

		return -1;
	}

	if (IPC_shm_init(&shm_c2s_ser, 0x002A, 0) || IPC_shm_init(&shm_s2c_ser, 0x002B, 0))
	{
		printf("IPC Shared memory configuration error!\n");

		return -1;
	}

	uint8_t client_ss[1024], server_ss[1024];
	size_t olen_cli = 0, olen_ser = 0;

	memset(client_ss, 0, sizeof(client_ss));
	memset(server_ss, 0, sizeof(server_ss));

	for (int n = 0; n < nRepeats; n++)
	{
		printf("########## ID = %d #########\n",n);
		if(0 == IPC_shm_write(shm_c2s_cli, 0, 0))
		{
			if(0 == IPC_shm_read(shm_s2c_cli, client_ss, &olen_cli))
			{
				printf("Client Read ss:\n");
				BIO_dump_fp(stdout, client_ss, olen_cli);
			}
		}

		if(0 == IPC_shm_write(shm_c2s_ser, 0, 0))
		{
			if(0 == IPC_shm_read(shm_s2c_ser, server_ss, &olen_ser))
			{
				printf("Server Read ss:\n");
				BIO_dump_fp(stdout, server_ss, olen_ser);
			}
		}
		if(olen_cli != olen_ser)
			break;
		if(memcmp(client_ss, server_ss, olen_cli))
			break;
	}
}

