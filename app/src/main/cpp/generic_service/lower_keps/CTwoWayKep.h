/*
 * CTwoWayKep.h
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */

#ifndef INCLUDE_CPP_CTWOWAYKEP_H_
#define INCLUDE_CPP_CTWOWAYKEP_H_

#include <iostream>
#include <string>

using namespace std;

#include "../../generic_service/CSerializable.h"
#include "../../generic_service/lower_keps/CKep.h"
#include "hybrid_kem.h"

class CTwoWayKep: public CKep, public CSerializable
{
public:
	string Pub, PubCp;
	string Priv;

	virtual string Serialize()
	{
		cout<<"serialization ... "<<Pub.size()<<endl;
		return CSerializable::ULL2Str(Pub.size()) + Pub;
	}

	virtual void Deserlize(string &str)
	{
		PubCp = str;
	}

public:
	CTwoWayKep();
	CTwoWayKep(string &name) :
			CKep(name)
	{

	}

	virtual ~CTwoWayKep();

	virtual int Keypair()
	{
		return 0;
	}
	virtual int Compute()
	{
		return 0;
	}

};

#endif /* INCLUDE_CPP_CTWOWAYKEP_H_ */
