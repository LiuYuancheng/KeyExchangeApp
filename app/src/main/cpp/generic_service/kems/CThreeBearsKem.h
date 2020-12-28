/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CTHREEBEARSKEM_H_
#define INCLUDE_CPP_CTHREEBEARSKEM_H_

#include "../../generic_service/kems/CKem.h"

class CThreeBearsKem: public CKem
{

public:
	CThreeBearsKem(string &pubkey, string &privkey);
	virtual ~CThreeBearsKem();

	int KeyGen();
	int Encaps();
	int Decaps();

	//static char  *Name;
};


#endif /* INCLUDE_CPP_CTHREEBEARSKEM_H_ */
