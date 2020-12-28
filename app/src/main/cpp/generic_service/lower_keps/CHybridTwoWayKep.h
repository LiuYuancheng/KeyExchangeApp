/*
 * CHybridKep.h
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CHYBRIDTWOWAYKEP_H_
#define CPP_CHYBRIDTWOWAYKEP_H_
#include <vector>

using namespace std;

#include "../lower_keps/CTwoWayKep.h"

#define HYBRID_KEP_MAX_SIZE  20

class CHybridTwoWayKep: public CTwoWayKep
{
public:
	vector<CTwoWayKep*> TwoWayKeps;

public:
	CHybridTwoWayKep();
	CHybridTwoWayKep(int count, CTwoWayKep *keps[])
	{
		this->SetTwoWayKeps(count, keps);
	}
	CHybridTwoWayKep(vector<CTwoWayKep*> &keps);
	virtual ~CHybridTwoWayKep();

	/* Overloaded */
	virtual int Keypair();
	virtual int Compute();

	int UpdateSharedStr()
	{
		vector<CTwoWayKep*>::iterator it =  TwoWayKeps.begin();

		while (it != TwoWayKeps.end())
		{
			this->SharedStr = (*it)->SharedStr;
			it++;
		}

		return 0;
	}

	int NextSharedStr(unsigned char *str)
	{
		UpdateSharedStr();
		memcpy(str, this->SharedStr.data(), this->SharedStr.length());

		return 0;
	}

	int SetTwoWayKeps(int count, CTwoWayKep *keps[])
	{
		for (int n = 0; n < count; n++)
			TwoWayKeps.push_back(keps[n]);

		return 0;
	}
	static int CreatAll(vector<string> ve)
	{

		return 0;
	}

	virtual string Serialize();
	virtual void Deserlize(string &str);

	string GetName()
	{
		vector<CTwoWayKep*>::iterator it = TwoWayKeps.begin();

		string name;

		name = name + '[';
		for (; it != TwoWayKeps.end(); it++)
		{
			name = name + (*it)->GetName();
			if (it != TwoWayKeps.end() - 1)
				name = name + ',';
		}
		name = name + ']';
		this->KepName = name;
		return name;
	}



};

#endif /* CPP_CHYBRIDTWOWAYKEP_H_ */
