/*
 * CNewHopeKem.h
 *
 *  Created on: 25 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CNEWHOPEKEM_H_
#define CPP_CNEWHOPEKEM_H_

#include "../../generic_service/kems/CKem.h"

class CNewHopeKem: public CKem
{
public:
	CNewHopeKem(string &pubkey, string &privkey);
	virtual ~CNewHopeKem();

	int KeyGen();
	int Encaps();
	int Decaps();
};

#endif /* CPP_CNEWHOPEKEM_H_ */
