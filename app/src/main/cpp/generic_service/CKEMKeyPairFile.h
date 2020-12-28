/*
 * CKEMKeyPairFile.h
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CKEMKEYPAIRFILE_H_
#define CPP_CKEMKEYPAIRFILE_H_

#include "../generic_service/CKEMKeyPairSouce.h"

class CKEMKeyPairFile:  public CKEMKeyPairSouce
{
public:
	CKEMKeyPairFile();
	virtual ~CKEMKeyPairFile();
};

#endif /* CPP_CKEMKEYPAIRFILE_H_ */
