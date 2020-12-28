/*
 * CKeConn.cpp
 *
 *  Created on: 22 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/comm/CKeConn.h"

#include "../../generic_service/lower_keps/CTwoWayKep.h"
#include "../keps/CAppKep.h"

CKeConn::CKeConn(string& srcid, string& distid, CKep* kep)
{
	SrcID = srcid;
	DstID  = distid;
	Kep = kep;

	pthread_mutex_init(&this->lock, NULL);

}
CKeConn::~CKeConn()
{
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&lock);
}

void CKeConn::Request()
{
//		Kep->Keypair();
//
//		cout << "===============" << CKeGateWay::Config.IpTable.at(ID) << endl;
//		Comm->SetSendAddr(CKeGateWay::Config.IpTable.at(ID));
//
//		string msg = keconn->Serialize();
//
//	//	BIO_dump_fp(stdout, msg.data(), msg.size());
//
//		cout << msg.size() << endl;
//
//		CTcpComm::Client();
//
//		string substr = msg.substr(0, 8);
//		cout << "############################################## ShareWith,   Write "
//				<< CSerializable::Str2ULL(substr) << "  " << msg.size() << " bytes"
//				<< endl;
//
//		Comm->Send(msg);
//
//		string str = CKeGateWay::Comm->Recv(sizeof(size_t));
//
//		size_t nbytes = CSerializable::Str2ULL(str);
//
//		cout << "############################################## ShareWith,   Read "
//				<< nbytes << " bytes" << endl;
//
//		string str2 = CKeGateWay::Comm->Recv(nbytes);
//
//	//	BIO_dump_fp(stdout, str.data(), str.size());
//	//
//	//	BIO_dump_fp(stdout, str2.data(), str2.size());
//
//		string str3 = str2.substr(0, sizeof(size_t));
//		size_t srcIDlen = CSerializable::Str2ULL(str3);
//		string srcID = str2.substr(sizeof(size_t), srcIDlen);
//
//		keconn->Deserlize(str2);
//
//		keconn->Kep->Compute();
//
//		string ss = keconn->Kep->SharedStr;
//
//		CKeGateWay::callback((unsigned char*) ss.c_str(), ss.size());
//
//	//
//	//	string str = Comm->Read(4);
//	//
//	//	keconn->Deserlize(str);
//	//
//	//	keconn->Kep->Compute();
//
//	//	KeConns.remove(keconn);
//
//		CTcpComm::RmClient();

}
