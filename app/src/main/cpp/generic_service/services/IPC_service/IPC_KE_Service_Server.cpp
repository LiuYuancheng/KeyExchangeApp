/*
 * GW_Alice.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include <pthread.h>
#include <signal.h>
#include <unistd.h>

#include <openssl/bio.h>
#include <iostream>
#include <libipc/ipc_shm_generic.h>
#include <map>

using namespace std;

#include "../../../generic_service/lower_keps/CHybridTwoWayKep.h"
#include "../../../generic_service/lower_keps/CKemTwoWayKep.h"
#include "../../../generic_service/kems/CHybridKem.h"
#include "../../../generic_service/CKeGateWay.h"
#include "../../../generic_service/kems/CRsaKem.h"
#include "../../../generic_service/kems/CBikeKem.h"
#include "../../../generic_service/CGatewayConfig.h"






static uint8_t current_ss[1024] =
{ 0 };
static size_t ss_len = 0;

volatile static int ss_valid = 0;

static map<string,string> sslist;



void OnShared(string ss, string sessionid)
{
	static int key_id = 0;

	cout << "INFO: Shared secrets: KEY_ID = " << key_id << endl;
	BIO_dump_fp(stdout, ss.data(), ss.length());

	memcpy(::current_ss, ss.data(), ss.length());

	sslist.insert(pair<string,string>(sessionid, ss));

	//sslist.insert(pair<string,string>)

	ss_len = ss.length();

		ss_valid = 1;


	key_id ++;
//	FILE *fp = fopen("Bob.out", "a+");
//	BIO_dump_fp(fp, ss, nbytes);
//	fputs("\n", fp);
//
//	fclose(fp);

}

int main(int argc, char *argv[])
{
	string cfgfile(argv[1]), ipTablefile(argv[2]);

	if (CKeGateWay::Start(cfgfile, ipTablefile, OnShared))
	{
		cout << "KEP GW start failed" << endl;

		return -1;
	}
	cout << "KEP GW start success" << endl;

	/*	set shared memory*/
	struct IPC_shm *shm_c2s, *shm_s2c;

	if (IPC_shm_init(&shm_c2s, 0x002A, 1) || IPC_shm_init(&shm_s2c, 0x002B, 1))
	{
		printf("IPC Shared memory configuration error!\n");

		return -1;
	}

	while (1)
	{
		size_t len;

		if (0 == IPC_shm_read(shm_c2s, 0, &len))
		{
			while (ss_valid != 1)
				;
			ss_valid = 0;
			if (0 == IPC_shm_write(shm_s2c, current_ss, ss_len))
			{
				continue;
			}
		}
	}

	pause();

	//CKeGateWay::ShareWith("Bob");

	/*
	 CGatewayConfig gwconfig;

	 gwconfig.LoadFile("gw.cfg");

	 cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	 cout << gwconfig.ID << endl;

	 cout << "RSA private key:" << endl;
	 cout << gwconfig.PrivKeys.at("RSA") << endl;
	 BIO_dump_fp(stdout, gwconfig.PrivKeys.at("RSA").data(),
	 gwconfig.PrivKeys.at("RSA").size());

	 cout << "BIKE private key:" << endl;
	 BIO_dump_fp(stdout, gwconfig.PrivKeys.at("BIKE").data(),
	 gwconfig.PrivKeys.at("BIKE").size());

	 cout << "Alice RSA public key:" << endl;
	 BIO_dump_fp(stdout, gwconfig.PubKeyTable.at("Alice").at("RSA").data(),
	 gwconfig.PubKeyTable.at("Alice").at("RSA").size());

	 cout << "Alice BIKE public key:" << endl;
	 BIO_dump_fp(stdout, gwconfig.PubKeyTable.at("Alice").at("BIKE").data(),
	 gwconfig.PubKeyTable.at("Alice").at("BIKE").size());

	 cout << "Bob RSA public key:" << endl;
	 BIO_dump_fp(stdout, gwconfig.PubKeyTable.at("Bob").at("RSA").data(),
	 gwconfig.PubKeyTable.at("Bob").at("RSA").size());

	 cout << "Bob BIKE public key:" << endl;
	 BIO_dump_fp(stdout, gwconfig.PubKeyTable.at("Bob").at("BIKE").data(),
	 gwconfig.PubKeyTable.at("Bob").at("BIKE").size());

	 cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	 */

	return 0;
}
