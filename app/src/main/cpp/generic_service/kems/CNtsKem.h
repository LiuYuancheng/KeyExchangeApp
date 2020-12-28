/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CNTSKEM_H_
#define INCLUDE_CPP_CNTSKEM_H_

#include "../../generic_service/kems/CKem.h"

class CNtsKem: public CKem
{

public:
	CNtsKem(string &pubkey, string &privkey);
	virtual ~CNtsKem();

	int KeyGen();
	int Encaps();
	int Decaps();

};


#endif /* INCLUDE_CPP_CNTSKEM_H_ */
