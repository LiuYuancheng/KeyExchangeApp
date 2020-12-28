/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CROLLOKEM_H_
#define INCLUDE_CPP_CROLLOKEM_H_

#include "../../generic_service/kems/CKem.h"

class CRolloKem: public CKem
{

public:
	CRolloKem(string &pubkey, string &privkey);
	virtual ~CRolloKem();

	int KeyGen();
	int Encaps();
	int Decaps();

};


#endif /* INCLUDE_CPP_CROLLOKEM_H_ */
