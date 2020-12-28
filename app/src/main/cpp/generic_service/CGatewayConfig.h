/*
 * CGatewayConfig.h
 *
 *  Created on: 22 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CGATEWAYCONFIG_H_
#define CPP_CGATEWAYCONFIG_H_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#include <string>
#include <map>

using namespace std;
using namespace libconfig;

class CGatewayConfig
{
public:
	string ID;
	string ServerID;
#define GATEWAY_ROLE_SERVER		0x01
#define GATEWAY_ROLE_CLIENT		0x02
	int Role;

#define GATEWAY_MODE_CS			0x01
#define GATEWAY_MODE_P2P		0x02
	int Mode;

	int PresetStatusFlag;  // 0, No; 1, Yes

	map<string, string> PrivKeys;
	map<string, map<string, string>> PubKeyTable;
	string DH_p, DH_g;

	map<string, string> IpTable;

public:
	CGatewayConfig();
	virtual ~CGatewayConfig();

	int LoadConfig(char *filename);
	int LoadIpTable(char *filename);

	/* static function*/
private:
	static string Base64Decoder(string &base64str);
	static string Base64FileDecoder(string &filename);
};

#endif /* CPP_CGATEWAYCONFIG_H_ */
