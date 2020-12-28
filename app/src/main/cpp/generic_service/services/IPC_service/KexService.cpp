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

using namespace std;

#include "../../../generic_service/CKeGateWay.h"


void OnShared(string ss, string sessionid) {
	static int key_id = 0;

	cout << "INFO: Shared secrets: KEY_ID = " << key_id << endl;
	LOG(INFO) << "Shared secretes, KEYID = " << key_id;
	BIO_dump_fp(stdout, ss.data(), ss.length());
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		cout << "usage:\n\t" << "./KexService <config file> <IP table file>" << endl;

		return 0;
	}
	string cfgfile(argv[1]), ipTablefile(argv[2]);

	google::InitGoogleLogging(argv[0]);

	FLAGS_log_dir = "../logs/";

	if (CKeGateWay::Start(cfgfile, ipTablefile, OnShared)) {
		cout << "KEP GW start failed" << endl;
		LOG(FATAL) << "Gateway fails to start!";

		return -1;
	}
	cout << "KEP GW start success" << endl;
	LOG(INFO) << "Gateway started.";

	pause();

	return 0;
}
