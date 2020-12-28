/*
 * CKEP.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CKEP_H_
#define INCLUDE_CPP_CKEP_H_

#include "../comm/CComm.h"

#include <string>

using namespace std;

#include <string.h>
#include <inttypes.h>
#include <stddef.h>

class CKep
{
public:
	string KepName;

	string SharedStr;


public:
	CKep();
	CKep(string &name)
	{
		KepName = name;
	}

	virtual ~CKep();


	virtual string GetName()
	{
		return KepName;
	}

	virtual int Setup(CComm *comm){
		return 0;
	}

	virtual int DoKe(CComm *comm)
	{
		return 0;
	}
	virtual int OnKe(CComm *comm)
	{
		return 0;
	}
};

#endif /* INCLUDE_CPP_CKEP_H_ */
