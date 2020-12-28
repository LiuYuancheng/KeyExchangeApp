/*
 * CDhKep.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CDHKEP_H_
#define CPP_CDHKEP_H_

#include "../../generic_service/lower_keps/CTwoWayKep.h"
#include "../non_quantum_safe/DHKE/dh_ke.h"
#include "hybrid_kem.h"

class CDhKep: public CTwoWayKep
{
private:
	string ParamP;
	string ParamG;
public:
	CDhKep();
	CDhKep(string &p, string &g);
	CDhKep(int);
	virtual ~CDhKep();

	int SetUp();
	int ReSetUp();

	int Keypair()
	{
		unsigned char *pk = new unsigned char[DH_PUBLICKEYBYTES];
		unsigned char *sk = new unsigned char[DH_SECRETKEYBYTES];

		DH_keypair(pk, sk, (unsigned char*) ParamP.data(),
				(unsigned char*) ParamG.data());

		string pkstr((char*) pk, DH_PUBLICKEYBYTES);
		string skstr((char*) sk, DH_SECRETKEYBYTES);

		this->Priv = skstr;
		this->Pub = pkstr;

		delete[] pk;
		delete[] sk;

		return 0;
	}
	int Compute()
	{
		unsigned char *sd = new unsigned char[DH_BYTES];

		DH_compute_and_derive(sd, (unsigned char*) PubCp.data(),
				(unsigned char*) Priv.data(), (unsigned char*) ParamP.data(),
				(unsigned char*) ParamG.data());

		string sdstr((char*) sd, DH_BYTES);
		this->SharedStr = sdstr;

		delete[] sd;

		return 0;
	}


//	string Serialize();
//
//	void Deserlize(string &str);
};

#endif /* CPP_CDHKEP_H_ */
