/*
 * CNewHopeKem.h
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CRQCKEM_H_
#define CPP_CRQCKEM_H_

#include "../../generic_service/kems/CKem.h"

class CRqcKem: public CKem
{
public:
	CRqcKem(string &pubkey, string &privkey);
	virtual ~CRqcKem();

	int KeyGen();
	int Encaps();
	int Decaps();
};

#endif /* CPP_CRQCKEM_H_ */
