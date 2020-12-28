/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CROUND5KEM_H_
#define INCLUDE_CPP_CROUND5KEM_H_

#include "../../generic_service/kems/CKem.h"

class CRound5Kem: public CKem
{

public:
	CRound5Kem(string &pubkey, string &privkey);
	virtual ~CRound5Kem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};

//char * CRsaKem::Name = "RSA-KEM";

#endif /* INCLUDE_CPP_CROUND5KEM_H_ */
