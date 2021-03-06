/*
 * CKemTwoWayKep.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */
#include "../../generic_service/lower_keps/CKemTwoWayKep.h"

#include <openssl/sha.h>
#include <string.h>

#include "../../generic_service/lower_keps/CTwoWayKep.h"

CKemTwoWayKep::CKemTwoWayKep(CKem *mykem, CKem *urkem)
{
	this->MyKem = mykem;
	this->UrKem = urkem;

	this->KepName = mykem->MajorName;

}

CKemTwoWayKep::~CKemTwoWayKep()
{

}

int CKemTwoWayKep::SetUrKem(CKem *urkem)
{
	this->UrKem = urkem;

	return 0;
}

int CKemTwoWayKep::Keypair()
{

	UrKem->Encaps();
	Pub = UrKem->CipherText;
	Priv = UrKem->SharedStr;

	return 0;
}
int CKemTwoWayKep::Compute()
{
	int sssize;

	MyKem->CipherText = PubCp;

	MyKem->Decaps();

	size_t sslen =
			(MyKem->SharedStr.size() < UrKem->SharedStr.size()) ?
					MyKem->SharedStr.size() : UrKem->SharedStr.size();
	const char *ss1 = MyKem->SharedStr.data();
	const char *ss2 = UrKem->SharedStr.data();
	char *ss = new char[sslen];

	for(int n = 0; n < sslen; n++)
	{
		ss[n] = ss1[n] ^ ss2[n];
	}

	string SS(ss, sslen);

	SharedStr = SS;

	delete[] ss;

	return 0;
}

//string& CKemTwoWayKep::Serialize()
//{
//	cout<<"CKemTwoWayKep::Serialize called"<<endl;
//
//	string s;
//
//	cout<<"CKemTwoWayKep::Serialize called"<<endl;
//
//	return s;
//}
//void CKemTwoWayKep::Deserlize()
//{
//
//}
//void CKemTwoWayKep::Deserlize(string&)
//{
//
//}

//string CKemTwoWayKep::Serialize()
//{
//	cout << "CKemTwoWayKep::Serialize called" << endl;
//
//	this->SeBuffer = this->Pub;
//
//
//	cout<< "Serialized "<<this->SeBuffer.size() << "bytes."<<endl;
//	cout << "CKemTwoWayKep::Serialize returned" << endl;
//
//	return CSerializable::ULL2Str(this->SeBuffer.size()) + this->SeBuffer;
//
//}
//
//void CKemTwoWayKep::Deserlize(string &str)
//{
//	cout << "CKemTwoWayKep::Deserlize called" << endl;
//	cout<< "Deserialize "<<str.size() << "bytes."<<endl;
//
//	this->DeBuffer = str;
//	this->PubCp = str;
//
//	cout << "CKemTwoWayKep::Deserlize returned" << endl;
//
//}
