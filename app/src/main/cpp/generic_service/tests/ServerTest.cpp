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

using namespace std;

#include "../../generic_service/lower_keps/CHybridTwoWayKep.h"
#include "../../generic_service/lower_keps/CKemTwoWayKep.h"
#include "../../generic_service/kems/CHybridKem.h"
#include "../../generic_service/CKeGateWay.h"
#include "../../generic_service/kems/CRsaKem.h"
#include "../../generic_service/kems/CBikeKem.h"
#include "../../generic_service/CGatewayConfig.h"
#include "../../generic_service/CSharedSecretManager.h"




void OnShared(unsigned char *ss, size_t nbytes)
{
	static int key_id = 0;

	cout<<"INFO: Shared secrets: KEY_ID = "<<++key_id<<endl;
	BIO_dump_fp(stdout, ss, nbytes);


//	FILE *fp = fopen("Bob.out", "a+");
//	BIO_dump_fp(fp, ss, nbytes);
//	fputs("\n", fp);
//
//	fclose(fp);


}

int main()
{
	string cfgfile("../gw_bob.cfg");

	if (CKeGateWay::Start(cfgfile, OnShared))
	{
		cout << "KEP GW start failed" << endl;

		return -1;
	}
	cout << "KEP GW start success" << endl;


	pause();


	return 0;
}
