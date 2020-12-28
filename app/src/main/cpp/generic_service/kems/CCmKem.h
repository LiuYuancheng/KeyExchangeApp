/*
 * CBikeKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CCMKEM_H_
#define INCLUDE_CPP_CCMKEM_H_

#include "../../generic_service/kems/CKem.h"

class CCmKem: public CKem
{

public:
	CCmKem(string &pubkey, string &privkey);
	virtual ~CCmKem();

	int KeyGen();
	int Encaps();
	int Decaps();

};



#endif /* INCLUDE_CPP_CCMKEM_H_ */
