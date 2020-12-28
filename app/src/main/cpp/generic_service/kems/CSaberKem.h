/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CSABERKEM_H_
#define INCLUDE_CPP_CSABERKEM_H_

#include "../../generic_service/kems/CKem.h"

class CSaberKem: public CKem
{

public:
	CSaberKem(string &pubkey, string &privkey);
	virtual ~CSaberKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};


#endif /* INCLUDE_CPP_CSABERKEM_H_ */
