/*
 * CHybridKep.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */
#include "../../generic_service/lower_keps/CHybridTwoWayKep.h"

#include <string.h>

#include "../../generic_service/lower_keps/CTwoWayKep.h"

CHybridTwoWayKep::CHybridTwoWayKep()
{
	// TODO Auto-generated constructor stub

}

CHybridTwoWayKep::~CHybridTwoWayKep()
{
	// TODO Auto-generated destructor stub
}

int CHybridTwoWayKep::Keypair()
{
	vector<CTwoWayKep*>::iterator it = TwoWayKeps.begin();
	cout << TwoWayKeps.size() << endl;

	this->Pub.clear();
	this->Priv.clear();
	for (; it != TwoWayKeps.end(); it++)
	{
		((CTwoWayKep*) (*it))->Keypair();
		this->Pub = this->Pub + ((CTwoWayKep*) (*it))->Pub;
		this->Priv = this->Priv + ((CTwoWayKep*) (*it))->Priv;
	}

	return 0;
}

int CHybridTwoWayKep::Compute()
{
	vector<CTwoWayKep*>::iterator it = TwoWayKeps.begin();

	this->SharedStr.clear();

	for (; it != TwoWayKeps.end(); it++)
	{
		((CTwoWayKep*) (*it))->Compute();
		this->SharedStr = this->SharedStr + ((CTwoWayKep*) (*it))->SharedStr;
	}

	return 0;
}

string CHybridTwoWayKep::Serialize()
{
	vector<CTwoWayKep*>::iterator it = this->TwoWayKeps.begin();

	this->SeBuffer.clear();
	for (; it != TwoWayKeps.end(); it++)
	{
		string str = (*it)->Serialize();
		this->SeBuffer = this->SeBuffer + str;
	}
	this->SeBuffer = CSerializable::ULL2Str(SeBuffer.size()) + this->SeBuffer;

	return this->SeBuffer;
}

void CHybridTwoWayKep::Deserlize(string &str)
{
	cout << "Deserlize " << str.size() << "bytes." << endl;

	size_t offset = 0;
	vector<CTwoWayKep*>::iterator it = TwoWayKeps.begin();

	for (; it != TwoWayKeps.end(); it++)
	{
		string lenstr = str.substr(offset, sizeof(size_t));
		size_t len = CSerializable::Str2ULL(lenstr);
		offset += sizeof(size_t);
		string substr = str.substr(offset, len);
		(*it)->Deserlize(substr);
		offset += len;
	}

}

