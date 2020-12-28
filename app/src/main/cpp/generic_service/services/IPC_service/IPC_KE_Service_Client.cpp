/*
 * GW_Alice.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#include<stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <openssl/bio.h>
#include <iostream>
#include <glog/logging.h>
#include <libipc/ipc_shm_generic.h>

using namespace std;

#include "../../../generic_service/lower_keps/CHybridTwoWayKep.h"
#include "../../../generic_service/lower_keps/CKemTwoWayKep.h"
#include "../../../generic_service/kems/CHybridKem.h"
#include "../../../generic_service/CKeGateWay.h"
#include "../../../generic_service/kems/CRsaKem.h"
#include "../../../generic_service/kems/CBikeKem.h"
#include "../../../generic_service/CGatewayConfig.h"


static char *KEMs[] =
{ "RSA-KEM", "BIKE-KEM" };

static CKeGateWay *GW_Alice, *GW_Bob;

static uint8_t current_ss[1024] =
{ 0 };
static size_t ss_len = 0;
static volatile int ss_valid = 0;

void OnShared(string ss, string sessionid)
{
	static int key_id = 0;

	cout << "INFO: Shared secrets: KEY_ID = " << key_id << endl;
	LOG(INFO)<<"Shared secretes, KEYID = "<<key_id;
	BIO_dump_fp(stdout, ss.data(), ss.length());

	memcpy(::current_ss, ss.data(), ss.length());
	ss_len = ss.length();
	if (key_id != 0)
	{
		ss_valid = 1;
	}
	key_id ++;

//	FILE *fp = fopen("Alice.out", "a+");
//	BIO_dump_fp(fp, ss, nbytes);
//	fputs("\n", fp);
//
//	fclose(fp);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout<<"usage:\n\t"<<"./IPC_KE_Service_Client <config file> <IP table file>"<<endl;

		return 0;
	}
	string cfgfile(argv[1]), ipTablefile(argv[2]);

	google::InitGoogleLogging(argv[0]);

	FLAGS_log_dir = "../logs/";

	if (CKeGateWay::Start(cfgfile, ipTablefile, OnShared))
	{
		cout << "KEP GW start failed" << endl;
		LOG(FATAL)<<"Gateway fails to start!";

		return -1;
	}
	cout << "KEP GW start success" << endl;
	LOG(INFO)<<"Gateway started.";

	/*	set shared memory*/
	struct IPC_shm *shm_c2s, *shm_s2c;

	if (IPC_shm_init(&shm_c2s, (int)0x001A, (int)1) || IPC_shm_init(&shm_s2c, (int)0x001B, (int)1))
	{
		printf("IPC Shared memory configuration error!\n");

		return -1;
	}

	//CKeGateWay::ShareWith((char*)"Bob");

	char  sessionID[65] = {0};

	while (1)
	{
		size_t len;
		string sss;

		memset(sessionID, 0, sizeof(sessionID));

		if (0 == IPC_shm_read(shm_c2s, (unsigned char*)sessionID, &len))
		{
			printf("sessionID for IPC: %s\n", sessionID);
			CKeGateWay::ShareWith((char*)"Bob", sessionID, sss);
			if (0 == IPC_shm_write(shm_s2c, current_ss, ss_len))
			{
				continue;
			}
		}
	}

	cout << "Running KEP:" << endl;
	cout << CKeGateWay::InstalledKeps("Alice", "Bob") << endl;

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
