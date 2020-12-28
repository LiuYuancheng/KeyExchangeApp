/*
 * CGatewayConfig.cpp
 *
 *  Created on: 22 Feb 2020
 *      Author: yiwen
 */
#include "../generic_service/CGatewayConfig.h"

#include <stdio.h>
#include <mbedtls/base64.h>
#include <iostream>

using namespace std;

CGatewayConfig::CGatewayConfig() {
	// TODO Auto-generated constructor stub

}

CGatewayConfig::~CGatewayConfig() {
	// TODO Auto-generated destructor stub
}

string CGatewayConfig::Base64FileDecoder(string &filename) {
	string binstr, base64str;
	size_t len, olen;
	unsigned char *base64;

	cout << filename << endl;
	FILE *fp = fopen(filename.c_str(), "r");

	fseek(fp, 0, SEEK_END);
	len = ftell(fp);

	base64 = (unsigned char*) malloc(len * 2 + 10);

	rewind(fp);
	fread(base64, 1, len, fp);

	if (mbedtls_base64_decode(base64 + len, len, &olen, base64, len))
		return binstr;

	string binstr2((char*) base64 + len, olen);
	cout << "len" << olen << endl;

	free(base64);
	fclose(fp);

	return binstr2;
}
string CGatewayConfig::Base64Decoder(string &base64str) {
	string binstr;
	size_t len, olen;
	unsigned char *base64;

	base64 = (unsigned char*) malloc(len * 2 + 10);

	if (mbedtls_base64_decode(base64 + len, len, &olen, base64, len))
		return binstr;

	string binstr2((char*) base64 + len, olen);

	return binstr2;
}

int CGatewayConfig::LoadConfig(char *filename) {
	Config cfg;

	try {
		cfg.readFile(filename);
	} catch (const FileIOException &fioex) {
		std::cerr << "I/O error while reading file." << std::endl;
		return (EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
		return (EXIT_FAILURE);
	}

	try {
		string GatewayID = cfg.lookup("GatewayID");

		this->ID = GatewayID;

		cout << "GatewayID: " << GatewayID << endl;
	} catch (const SettingNotFoundException &nfex) {
		cerr << "No 'name' setting in configuration file." << endl;
	}

	try {
		string Mode = cfg.lookup("Mode");
		string strCS("CS");

		if (Mode == strCS) {
			this->Mode = GATEWAY_MODE_CS;
			cout << "Mode: C/S" << endl;

		} else {
			this->Mode = GATEWAY_MODE_P2P;
			cout << "Mode: P2P" << endl;
		}

	} catch (const SettingNotFoundException &nfex) {
		cerr << "No 'Mode' setting in configuration file." << endl;
	}
	try {
		if (this->Mode == GATEWAY_MODE_CS) {
			string Role = cfg.lookup("Role");
			string strC("C");

			if (Role == strC) {
				this->Role = GATEWAY_ROLE_CLIENT;
				cout << "Role: Client" << endl;

			} else {
				this->Role = GATEWAY_ROLE_SERVER;
				cout << "Role: Server" << endl;
			}

			if (this->Role == GATEWAY_ROLE_CLIENT) {
				string ServerID = cfg.lookup("ServerID");

				this->ServerID = ServerID;

				cout << "ServerID: " << this->ServerID << endl;

				string flag = cfg.lookup("PresetInitialStatus");
				string strNo("No");

				if (flag == strNo) {
					this->PresetStatusFlag = 0;
					cout << "PresetStatusFlag: No" << endl;

				} else {
					this->PresetStatusFlag = 1;
					cout << "PresetStatusFlag: Yes" << endl;

				}
			}
		}
	} catch (const SettingNotFoundException &nfex) {
		cerr << "No 'Role', 'ServerID' or 'PresetInitialStatus' setting in configuration file." << endl;
	}

	const Setting &root = cfg.getRoot();

	try {
		const Setting &book = root["DHParamFiles"];
		string keyfile;

		if (book.lookupValue("ParamP", keyfile)) {
			string name("DHParamP");

			this->DH_p = CGatewayConfig::Base64FileDecoder(keyfile);

			cout << setw(30) << left << "ParamP = " << keyfile << "  " << endl;
		}

		if (book.lookupValue("ParamG", keyfile)) {
			string name("DHParamG");

			this->DH_g = CGatewayConfig::Base64FileDecoder(keyfile);

			cout << setw(30) << left << "ParamG = " << keyfile << "  " << endl;
		}

	} catch (const SettingNotFoundException &nfex) {

	}
	try {

		const Setting &book = root["PrivateKeyFiles"];
		string keyfile;
		if (book.lookupValue("RSAKey", keyfile)) {
			string name("RSA");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "RSAKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("BikeKey", keyfile)) {
			string name("BIKE");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "BikeKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("FrodoKey", keyfile)) {
			string name("FRODO");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "FrodoKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("NewHopeKey", keyfile)) {
			string name("NEWHOPE");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "NewHopeKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("HqcKey", keyfile)) {
			string name("HQC");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "HqcKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("RqcKey", keyfile)) {
			string name("RQC");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "RqcKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("NtruKey", keyfile)) {
			string name("NTRU");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "NtruKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("NtruPrimeKey", keyfile)) {
			string name("NTRUPRIME");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "NtruPrimeKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("LedaKey", keyfile)) {
			string name("LEDA");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "LedaKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("LacKey", keyfile)) {
			string name("LAC");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "LacKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("SikeKey", keyfile)) {
			string name("SIKE");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "SikeKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("NtsKey", keyfile)) {
			string name("NTS");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "NtsKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("ThreeBearsKey", keyfile)) {
			string name("THREEBEARS");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "ThreeBearsKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("KyberKey", keyfile)) {
			string name("KYBER");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "KyberKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("SaberKey", keyfile)) {
			string name("SABER");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "SaberKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("RolloKey", keyfile)) {
			string name("ROLLO");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "RolloKey = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("Round5Key", keyfile)) {
			string name("ROUND5");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "Round5Key = " << keyfile << "  " << endl;
		}
		if (book.lookupValue("CmKey", keyfile)) {
			string name("CM");

			this->PrivKeys.insert(pair<string, string>(name, CGatewayConfig::Base64FileDecoder(keyfile)));
			cout << setw(30) << left << "CmKey = " << keyfile << "  " << endl;
		}

	} catch (const SettingNotFoundException &nfex) {
		cout << "error";
	}
	cout << endl;
	try {
		const Setting &books = root["PublicKeyTable"];
		int count = books.getLength();

		for (int i = 0; i < count; ++i) {
			string GatewayID, keyfile, Name;
			const Setting &book = books[i];

			if (!(book.lookupValue("GatewayID", GatewayID)))
				continue;

			cout << setw(30) << left << "GatewayID = " << GatewayID << "  " << endl;

			map<string, string> maptmp;

			const Setting &book2 = books[i]["PublicKeyFiles"];

			///////////////////////////////////////////////////////
			if (!book2.lookupValue("RSAKey", keyfile))
				continue;
			Name = "RSA";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "RSAKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("BikeKey", keyfile))
				continue;
			Name = "BIKE";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "BikeKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("FrodoKey", keyfile))
				continue;
			Name = "FRODO";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "BikeKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("NewHopeKey", keyfile))
				continue;
			Name = "NEWHOPE";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "NewHopeKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("HqcKey", keyfile))
				continue;
			Name = "HQC";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "HqcKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("RqcKey", keyfile))
				continue;
			Name = "RQC";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "RqcKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("NtruKey", keyfile))
				continue;
			Name = "NTRU";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "NtruKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("NtruPrimeKey", keyfile))
				continue;
			Name = "NTRUPRIME";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "NtruPrimeKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("LedaKey", keyfile))
				continue;
			Name = "LEDA";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "LedaKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("LacKey", keyfile))
				continue;
			Name = "LAC";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "LacKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("SikeKey", keyfile))
				continue;
			Name = "SIKE";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "SikeKey = " << keyfile << "  " << endl;
			///////////////////////////////////////////////////////
			if (!book2.lookupValue("NtsKey", keyfile))
				continue;
			Name = "NTS";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "NtsKey = " << keyfile << "  " << endl;
			if (!book2.lookupValue("ThreeBearsKey", keyfile))
				continue;
			Name = "THREEBEARS";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "ThreeBearsKey = " << keyfile << "  " << endl;
			if (!book2.lookupValue("KyberKey", keyfile))
				continue;
			Name = "KYBER";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "KyberKey = " << keyfile << "  " << endl;
			if (!book2.lookupValue("SaberKey", keyfile))
				continue;
			Name = "SABER";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "SaberKey = " << keyfile << "  " << endl;
			if (!book2.lookupValue("RolloKey", keyfile))
				continue;
			Name = "ROLLO";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "RolloKey = " << keyfile << "  " << endl;
			if (!book2.lookupValue("Round5Key", keyfile))
				continue;
			Name = "ROUND5";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "Round5Key = " << keyfile << "  " << endl;
			if (!book2.lookupValue("CmKey", keyfile))
				continue;
			Name = "CM";
			maptmp.insert(pair<string, string>(Name, CGatewayConfig::Base64FileDecoder(keyfile)));

			cout << setw(30) << left << "CmKey = " << keyfile << "  " << endl;
//////////////////////////////////////////////////////////////////////
			this->PubKeyTable.insert(pair<string, map<string, string>>(GatewayID, maptmp));

		}

	} catch (const SettingNotFoundException &nfex) {
		// Ignore.
		cout << "error";
	}

	return 0;
}

int CGatewayConfig::LoadIpTable(char *filename) {
	Config cfg;

	try {
		cfg.readFile(filename);
	} catch (const FileIOException &fioex) {
		std::cerr << "I/O error while reading file." << std::endl;
		return (EXIT_FAILURE);
	} catch (const ParseException &pex) {
		std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
		return (EXIT_FAILURE);
	}

	const Setting &root = cfg.getRoot();

	cout << "=================================================" << endl;
	cout << "IP Table:" << endl;
	cout << "-------------------------------------------------" << endl;

	try {
		const Setting &books = root["TCPAddr"];
		int count = books.getLength();

		for (int i = 0; i < count; ++i) {
			string GatewayID, SocketAddr;
			const Setting &book = books[i];

			if (!(book.lookupValue("GatewayID", GatewayID) && book.lookupValue("SocketAddr", SocketAddr)))
				continue;

			cout << setw(30) << left << GatewayID << " --> " << SocketAddr << endl;
			this->IpTable.insert(pair<string, string>(GatewayID, SocketAddr));

		}

	} catch (const SettingNotFoundException &nfex) {
		// Ignore.
		cout << "error";
	}
	cout << "=================================================" << endl;

	return 0;
}
