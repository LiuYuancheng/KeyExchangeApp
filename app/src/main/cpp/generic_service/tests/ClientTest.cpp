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

using namespace std;

#include <libqskep/CHybridTwoWayKep.h>
#include <libqskep/CKemTwoWayKep.h>
#include <libqskep/CHybridKem.h>
#include <libqskep/CKeGateWay.h>
#include "../../generic_service/CGatewayConfig.h"

#include "../../generic_service/qsss_ipc_client.h"




void OnShared(unsigned char *ss, size_t nbytes)
{
	static int key_id = 0;

	cout<<"INFO: Shared secrets: KEY_ID = "<<++key_id<<endl;
	BIO_dump_fp(stdout, (const char*)ss, nbytes);


//	FILE *fp = fopen("Alice.out", "a+");
//	BIO_dump_fp(fp, ss, nbytes);
//	fputs("\n", fp);
//
//	fclose(fp);
}

int main(int argc, char * argv[])
{
	int repeats;

	repeats = atoi(argv[1]);

	string cfgfile("../gw_alice.cfg");

	if (CKeGateWay::Start(cfgfile, OnShared))
	{
		cout << "KEP GW start failed" << endl;

		return -1;
	}
	cout << "KEP GW start success" << endl;

	for(int n = 0; n < repeats; n ++)
	{
		if(CKeGateWay::ShareWith((char*)"Bob") == 0)
		{
			cout<<"Shared."<<endl;
		}

	}


	return 0;
}
