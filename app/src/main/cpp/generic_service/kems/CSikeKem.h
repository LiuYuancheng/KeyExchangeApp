/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CSIKEKEM_H_
#define INCLUDE_CPP_CSIKEKEM_H_

#include "../../generic_service/kems/CKem.h"

class CSikeKem: public CKem
{

public:
	CSikeKem(string &pubkey, string &privkey);
	virtual ~CSikeKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};


#endif /* INCLUDE_CPP_CSIKEKEM_H_ */
