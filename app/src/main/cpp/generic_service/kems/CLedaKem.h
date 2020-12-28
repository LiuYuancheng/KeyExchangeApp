/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CLEDAKEM_H_
#define INCLUDE_CPP_CLEDAKEM_H_

#include "../../generic_service/kems/CKem.h"

class CLedaKem: public CKem
{

public:
	CLedaKem(string &pubkey, string &privkey);
	virtual ~CLedaKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};

//char * CRsaKem::Name = "RSA-KEM";

#endif /* INCLUDE_CPP_CLEDAKEM_H_ */
