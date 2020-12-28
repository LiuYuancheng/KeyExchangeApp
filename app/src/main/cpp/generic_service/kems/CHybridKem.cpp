/*
 * CHybridKem.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */
#include "../../generic_service/kems/CHybridKem.h"

#include <string.h>

#include "../../generic_service/kems/CBikeKem.h"
#include "../../generic_service/kems/CRsaKem.h"

CHybridKem::CHybridKem(int count, char *names[])
{
	// TODO Auto-generated constructor stub
	this->KemCount = count;
	for (int n = 0; n < count; n++)
	{
		if (strcmp(names[n], "RSA-KEM") == 0)
			this->Kems[n] = new CRsaKem();
		else if (strcmp(names[n], "BIKE-KEM") == 0)
			this->Kems[n] = new CFrodoKem();
	}


}

CHybridKem::CHybridKem(int count, CKem * kems[])
{
	this->KemCount = count;
	for (int n = 0; n < count; n++)
		this->Kems[n] = kems[n];


}


CHybridKem::~CHybridKem()
{
	for (int n = 0; n < KemCount; n++)
	{
		delete this->Kems[n];
	}
}

int CHybridKem::KeyGen()
{
	int ret = 0;

	for (int n = 0; n < KemCount; n++)
	{
		ret = ret || this->Kems[n]->KeyGen();
	}

	return ret;
}

int CHybridKem::Encaps()
{
	int ret = 0;

	for (int n = 0; n < KemCount; n++)
	{
		ret = ret || this->Kems[n]->Encaps();
	}

	return ret;
}

int CHybridKem::Decaps()
{
	int ret = 0;

	for (int n = 0; n < KemCount; n++)
	{
		ret = ret || this->Kems[n]->Decaps();
	}

	return ret;
}

