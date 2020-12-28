/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CNTRUPRIMEKEM_H_
#define INCLUDE_CPP_CNTRUPRIMEKEM_H_

#include "../../generic_service/kems/CKem.h"

class CNtruPrimeKem: public CKem
{

public:
	CNtruPrimeKem(string &pubkey, string &privkey);
	virtual ~CNtruPrimeKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};


#endif /* INCLUDE_CPP_CNTRUPRIMEKEM_H_ */
