/*
 * CDhKep.cpp
 *
 *  Created on: 20 Feb 2020
 *      Author: yiwen
 */
#include "../../generic_service/lower_keps/CDhKep.h"

#include <string.h>
#include <cstddef>
#include "../non_quantum_safe/DHKE/dh_ke.h"
#include <string>

#include "../../generic_service/lower_keps/CKep.h"

using namespace std;


CDhKep::CDhKep()
{

	// TODO Auto-generated constructor stub

}

CDhKep::CDhKep(int a)
{
	SetUp();
}


CDhKep::CDhKep(string &p, string &g)
{
	ParamP = p;
	ParamG = g;

	this->KepName = "DH-KE";
}

CDhKep::~CDhKep()
{

}

int CDhKep::SetUp()
{
	unsigned char *p, *g;
	int s1, s2;

	p = new unsigned char[DH_P_BYTES];
	g = new unsigned char[DH_G_BYTES];

	DH_setup(p, &s1, g, &s2);

	string str_p((char*) p, DH_P_BYTES), str_g((char*) g, DH_G_BYTES);

	ParamP = str_p;
	ParamG = str_g;

	delete[] p;
	delete[] g;

	return 0;
}

int CDhKep::ReSetUp()
{
	SetUp();

	return 0;
}

//string CDhKep::Serialize()
//{
//	cout << "CDhKep::Serialize called" << endl;
//
//	this->SeBuffer = this->Pub;
//
//	cout<< "Serialized "<<this->SeBuffer.size() << "bytes."<<endl;
//	cout << "CDhKep::Serialize returned" << endl;
//
//	return this->SeBuffer;
//}
//
//void CDhKep::Deserlize(string &str)
//{
//	cout << "CDhKep::Deserlize called" << endl;
//	cout<< "Serialized "<<str.size() << "bytes."<<endl;
//
//	this->DeBuffer = str;
//	this->PubCp = str;
//
//	cout << "CDhKep::Deserlize returned" << endl;
//
//}
