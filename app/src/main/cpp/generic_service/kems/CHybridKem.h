/*
 * CHybridKem.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CHYBRIDKEM_H_
#define INCLUDE_CPP_CHYBRIDKEM_H_

#include "../../generic_service/kems/CKem.h"

#define HYBRID_KEM_MAX_SIZE  20

class CHybridKem: public CKem
{
public:

	CKem *Kems[HYBRID_KEM_MAX_SIZE];
	int KemCount;

public:
	CHybridKem(int count, char * names[]);
	CHybridKem(int count, CKem * kems[]);
	virtual ~CHybridKem();

	int SetPubKey();
	int SetPrivKey();

	int GetPubKey();

	int KeyGen();
	int Encaps();
	int Decaps();


};

#endif /* INCLUDE_CPP_CHYBRIDKEM_H_ */
