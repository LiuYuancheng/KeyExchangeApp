/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CKYBERKEM_H_
#define INCLUDE_CPP_CKYBERKEM_H_

#include "../../generic_service/kems/CKem.h"

class CKyberKem: public CKem
{

public:
	CKyberKem(string &pubkey, string &privkey);
	virtual ~CKyberKem();

	int KeyGen();
	int Encaps();
	int Decaps();

};


#endif /* INCLUDE_CPP_CKYBERKEM_H_ */
