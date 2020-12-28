/*
 * CSharedSecretManager.h
 *
 *  Created on: 23 Apr 2020
 *      Author: yiwen
 */

#ifndef CPP_CSHAREDSECRETMANAGER_H_
#define CPP_CSHAREDSECRETMANAGER_H_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

class CSharedSecretManager
{
private:
	queue<string> SharedSecrets;
public:
	void DepositOctets(unsigned char *c_str, size_t len)
	{
		if (len > 0)
		{
			string str((char*)c_str, len);
			SharedSecrets.push(str);
		}
	}
	void WithdrawOctets(unsigned char *c_str, size_t *olen)
	{
		string str = SharedSecrets.front();
	    const char * s = str.c_str();

		*olen = str.size();
		memcpy(c_str, s, *olen);

		SharedSecrets.pop();
	}
	CSharedSecretManager();
	virtual ~CSharedSecretManager();
};

#endif /* CPP_CSHAREDSECRETMANAGER_H_ */
