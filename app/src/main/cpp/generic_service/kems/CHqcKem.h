/*
 * CNewHopeKem.h
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CHQCKEM_H_
#define CPP_CHQCKEM_H_

#include "../../generic_service/kems/CKem.h"

class CHqcKem: public CKem
{
public:
	CHqcKem(string &pubkey, string &privkey);
	virtual ~CHqcKem();

	int KeyGen();
	int Encaps();
	int Decaps();
};

#endif /* CPP_CHQCKEM_H_ */
