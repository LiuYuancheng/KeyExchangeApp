/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CLACKEM_H_
#define INCLUDE_CPP_CLACKEM_H_

#include "../../generic_service/kems/CKem.h"

class CLacKem: public CKem
{

public:
	CLacKem(string &pubkey, string &privkey);
	virtual ~CLacKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};

//char * CRsaKem::Name = "RSA-KEM";

#endif /* INCLUDE_CPP_CLACKEM_H_ */
