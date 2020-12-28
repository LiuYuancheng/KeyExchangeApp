/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CNTRUKEM_H_
#define INCLUDE_CPP_CNTRUKEM_H_

#include "../../generic_service/kems/CKem.h"

class CNtruKem: public CKem
{

public:
	CNtruKem(string &pubkey, string &privkey);
	virtual ~CNtruKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};


#endif /* INCLUDE_CPP_CNTRUKEM_H_ */
