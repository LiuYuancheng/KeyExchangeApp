/*
 * CUtility.h
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CUTILITY_H_
#define CPP_CUTILITY_H_

#include <stdio.h>
#include <openssl/bio.h>

class CUtility
{
public:
	CUtility();
	virtual ~CUtility();

	static int BIOd_dump_fp(FILE *fd, void * data, size_t len, size_t headN, size_t tailN)
	{
		unsigned char * p = new unsigned char[len];





		return 0;
	}

};

#endif /* CPP_CUTILITY_H_ */
