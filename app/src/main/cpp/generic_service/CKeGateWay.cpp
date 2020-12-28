/*
 * CKeGateWay.cpp
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */

#include "CKeGateWay.h"

#include "comm/CKeConn.h"
#include "comm/CTcpComm.h"
#include "kems/CBikeKem.h"
#include "kems/CCmKem.h"
#include "kems/CFrodoKem.h"
#include "kems/CHqcKem.h"
#include "kems/CKyberKem.h"
#include "kems/CLacKem.h"
#include "kems/CLedaKem.h"
#include "kems/CNewHopeKem.h"
#include "kems/CNtruKem.h"
#include "kems/CNtruPrimeKem.h"
#include "kems/CNtsKem.h"
#include "kems/CRolloKem.h"
#include "kems/CRound5Kem.h"
#include "kems/CRqcKem.h"
#include "kems/CRsaKem.h"
#include "kems/CSaberKem.h"
#include "kems/CSikeKem.h"
#include "kems/CThreeBearsKem.h"
#include "keps/CKepPhi.h"
#include "keps/CKepPsi.h"
#include "lower_keps/CDhKep.h"
#include "lower_keps/CHybridTwoWayKep.h"
#include "lower_keps/CKemTwoWayKep.h"
#include "lower_keps/CTwoWayKep.h"

#include <signal.h>
#include <stdlib.h>
#include <openssl/bio.h>

//string CKeGateWay::OwnID;
//int CKeGateWay::GWMode;
//int CKeGateWay::GWRole;
list<CKeConn*> CKeGateWay::KeConns;
CGatewayConfig CKeGateWay::Config;
CComm *CKeGateWay::Comm;
int CKeGateWay::SerSocket;
int CKeGateWay::UDPSerSocket;
int CKeGateWay::PresetStatusFlag;

void (*CKeGateWay::callback)(string, string) = NULL;

//CKeGateWay::CKeGateWay(string &configfile)
//{
//	Config.LoadConfig((char*) configfile.c_str());
//	OwnID = Config.ID;
//
//	Config.LoadIpTable("IPTable.cfg");
//	string addr = Config.IpTable.at(this->OwnID);
//	size_t pos = addr.find_first_of(':');
//
//	string ipaddr = addr.substr(0, pos);
//	int port = atoi(addr.substr(pos + 1, addr.size()).c_str());
//
//	cout << ipaddr << endl;
//	cout << port << endl;
//
//	Comm = new CTcpComm(ipaddr, port, OnShared);
//
//}
//
//CKeGateWay::~CKeGateWay()
//{
//	if (Comm != NULL)
//		delete Comm;
//}
void CKeGateWay::SignalHandler(int sig) {
	int ret = 0;

	cout << "Caught Signal: " << sig << endl;
	switch (sig) {
	case SIGINT:
		ret = close(CKeGateWay::SerSocket);			// close TCP server
		if (ret == 0) {
			//LOG(INFO) << "TCP server closed.";
			cout << "TCP server closed!" << endl;
		} else {
			cout << "errno: " << errno << endl;
		}
		ret = close(CKeGateWay::UDPSerSocket);		// close UDP server
		if (ret == 0) {
			//LOG(INFO) << "UDP server closed.";
			cout << "UDP server closed!" << endl;
		} else {
			cout << "errno: " << errno << endl;
		}
		exit(1);
	}
}

void CKeGateWay::RegisterEvent() {
	struct sigaction sigHandler;

	sigHandler.sa_handler = CKeGateWay::SignalHandler;
	sigemptyset(&sigHandler.sa_mask);
	sigHandler.sa_flags = 0;

	sigaction(SIGINT, &sigHandler, NULL);
}

int CKeGateWay::Start(string &configfile, string &ipTablefile, void (*callback)(string, string)) {

	CKeGateWay::Config.LoadConfig((char*) configfile.c_str());
	CKeGateWay::Config.LoadIpTable((char*) ipTablefile.c_str());

	CKeGateWay::callback = callback;

	pthread_t tidp;

	if ((CKeGateWay::Config.Mode == GATEWAY_MODE_CS && CKeGateWay::Config.Role == GATEWAY_ROLE_SERVER) || CKeGateWay::Config.Mode == GATEWAY_MODE_P2P) {
		CTcpComm::SerArg *arg = new CTcpComm::SerArg;
		string addr = CKeGateWay::Config.IpTable.at(CKeGateWay::Config.ID);
		cout << "addr = " << addr << endl;
		size_t pos = addr.find_first_of(':');

		string ipaddr = addr.substr(0, pos);
		int port = atoi(addr.substr(pos + 1, addr.size()).c_str());

		cout << ipaddr << endl;
		cout << port << endl;

		arg->IPaddr = ipaddr;
		arg->port = port;
		arg->callback = CKeGateWay::OnShared;
		arg->Socketfd = &CKeGateWay::SerSocket;

		if (pthread_create(&tidp, NULL, CKeGateWay::TCPServer, (void*) arg) == -1) {
			printf("create error!\n");

			return -1;
		}
	}
	if (pthread_create(&tidp, NULL, CKeGateWay::LocalUDPServer, NULL) == -1) {
		printf("create error!\n");

		return -1;
	}

	CKeGateWay::RegisterEvent();
	///////////////////////////////////////////////
	char randbytes[20] = { 0 };

	srand((unsigned) time(NULL));
	sprintf(randbytes, "%d", rand());
	randombytes_init((unsigned char*) randbytes, (unsigned char*) "kep", 256);

	if (CKeGateWay::Config.Mode == GATEWAY_MODE_CS && CKeGateWay::Config.Role == GATEWAY_ROLE_CLIENT && CKeGateWay::Config.PresetStatusFlag == 1) {
		string sharedSecret;
		CKeGateWay::ShareWith((char*) CKeGateWay::Config.ServerID.data(), NULL, sharedSecret);
	}

	return 0;
}

int CKeGateWay::Reload(CKep *kep) {
	return 0;
}

int CKeGateWay::Stop() {
	if (Comm != NULL)
		delete Comm;
	return 0;
}

int CKeGateWay::ShareWith(char ID[], char sessionID[], string &sharedSecret) {

	cout << "=======================================================================================" << endl;
	cout << "Starting a Key Exchange request" << endl;
	if (sessionID != NULL) {
		//LOG(INFO) << "SessionID: " << sessionID;
		cout << "SessionID: " << sessionID << endl;
	} else {
		//LOG(INFO) << "presetting ...";
		cout << "presetting ..." << endl;
	}

	CKeConn *keconn = GetKeConn(ID);

	if (keconn == NULL) {
		string dstId((char*) ID);
//		CKeGateWay::InitializePhi(dstId);
		CKeGateWay::InitializePsi(dstId);
		keconn = GetKeConn(ID);
	}

	keconn->Request();

	CTcpComm *conn = new CTcpComm();

	// cout << "distip: " << CKeGateWay::Config.IpTable.at(ID) << endl;
	string addr = CKeGateWay::Config.IpTable.at(ID);

	int cli_fd = 0, retrylimit = 10;

	cli_fd = CTcpComm::Connect((char*) CTcpComm::GetSocketAddrIP(addr).c_str(), CTcpComm::GetSocketAddrPort(addr));
	while (cli_fd < 0 && retrylimit > 0) {
		cout << "connecting fails, retrying for the " << 11 - retrylimit << " time(s) ..." << endl;
		retrylimit--;
		cout << "connecting ..." << endl;
		sleep(1);
		cli_fd = CTcpComm::Connect((char*) CTcpComm::GetSocketAddrIP(addr).c_str(), CTcpComm::GetSocketAddrPort(addr));
	};

	if (retrylimit <= 0) {
		//LOG(ERROR) << "retrying aborted, cannot connect to " << ID << " (" << addr << ")";
		cout << "ERROR: fails to connect to " << ID << " (" << addr << ")" << endl;
		exit(0);
	}

	conn->fd = cli_fd;

	keconn->Share(conn, sessionID);

	if (sessionID) {
		sharedSecret = keconn->Kep->SharedStr;
		CKeGateWay::callback(sharedSecret, sessionID);
	}
	close(cli_fd);

	return 0;
}

void CKeGateWay::OnShared(int fd) {
	CTcpComm *conn = new CTcpComm();
	conn->fd = fd;
	string data = conn->Recv(sizeof(size_t));
	size_t len = CSerializable::Str2ULL(data);
	string srcID = conn->Recv(len);
	data = conn->Recv(sizeof(size_t));
	len = CSerializable::Str2ULL(data);
	string dstID = conn->Recv(len);
	CKeConn *keconn = GetKeConn((char*) srcID.c_str());
	cout << srcID << endl;

	if (keconn == NULL) {
//		CKeGateWay::InitializePhi(srcID);
		CKeGateWay::InitializePsi(srcID);

		keconn = GetKeConn((char*) srcID.c_str());

	}

	data = conn->Recv(sizeof(size_t));

	len = CSerializable::Str2ULL(data);
	cout << "+++++ len: " << len;

	string sessionID = conn->Recv(len);
	cout << "++++++ len: " << sessionID.length();

	//LOG(INFO) << "SessionID: " << sessionID;
	cout << "SessionID: " << sessionID << endl;

	keconn->OnSharing(conn, (char*) sessionID.c_str());

	string ss = keconn->Kep->SharedStr;

	if (ss.size() > 0) {
		CKeGateWay::callback(ss, sessionID);
		keconn->Kep->SharedStr.clear();
	}

//	KeConns.remove(keconn);

}
int CKeGateWay::InitializePhi(string &urID) {
	CRsaKem *myrsakem, *urrsakem;
	CBikeKem *mybikekem, *urbikekem;
	CFrodoKem *myfrodokem, *urfrodokem;
	CNewHopeKem *mynewhopekem, *urnewhopekem;
	CHqcKem *myhqckem, *urhqckem;
	CRqcKem *myrqckem, *urrqckem;
	CNtruKem *myntrukem, *urntrukem;
	CNtruPrimeKem *myntruprimekem, *urntruprimekem;
	CLedaKem *myledakem, *urledakem;
	CLacKem *mylackem, *urlackem;
	CSikeKem *mysikekem, *ursikekem;
	CNtsKem *myntskem, *urntskem;
	CThreeBearsKem *mythreebearskem, *urthreebearskem;
	CKyberKem *mykyberkem, *urkyberkem;
	CSaberKem *mysaberkem, *ursaberkem;
	CRolloKem *myrollokem, *urrollokem;
	CRound5Kem *myround5kem, *urround5kem;
	CCmKem *mycmkem, *urcmkem;

	string nullstr;

	myrsakem = new CRsaKem(nullstr, Config.PrivKeys.at("RSA"));
	mybikekem = new CBikeKem(nullstr, Config.PrivKeys.at("BIKE"));
	myfrodokem = new CFrodoKem(nullstr, Config.PrivKeys.at("FRODO"));
	mynewhopekem = new CNewHopeKem(nullstr, Config.PrivKeys.at("NEWHOPE"));
	myhqckem = new CHqcKem(nullstr, Config.PrivKeys.at("HQC"));
	myrqckem = new CRqcKem(nullstr, Config.PrivKeys.at("RQC"));
	myntrukem = new CNtruKem(nullstr, Config.PrivKeys.at("NTRU"));
	myntruprimekem = new CNtruPrimeKem(nullstr, Config.PrivKeys.at("NTRUPRIME"));
	myledakem = new CLedaKem(nullstr, Config.PrivKeys.at("LEDA"));
	mylackem = new CLacKem(nullstr, Config.PrivKeys.at("LAC"));
	mysikekem = new CSikeKem(nullstr, Config.PrivKeys.at("SIKE"));
	myntskem = new CNtsKem(nullstr, Config.PrivKeys.at("NTS"));
	mythreebearskem = new CThreeBearsKem(nullstr, Config.PrivKeys.at("THREEBEARS"));
	mykyberkem = new CKyberKem(nullstr, Config.PrivKeys.at("KYBER"));
	mysaberkem = new CSaberKem(nullstr, Config.PrivKeys.at("SABER"));
	myrollokem = new CRolloKem(nullstr, Config.PrivKeys.at("ROLLO"));
	myround5kem = new CRound5Kem(nullstr, Config.PrivKeys.at("ROUND5"));
	mycmkem = new CCmKem(nullstr, Config.PrivKeys.at("CM"));
////////////////////////////////////////////////////////////////////////////////
	urrsakem = new CRsaKem(Config.PubKeyTable.at(urID).at("RSA"), nullstr);
	urbikekem = new CBikeKem(Config.PubKeyTable.at(urID).at("BIKE"), nullstr);
	urfrodokem = new CFrodoKem(Config.PubKeyTable.at(urID).at("FRODO"), nullstr);
	urnewhopekem = new CNewHopeKem(Config.PubKeyTable.at(urID).at("NEWHOPE"), nullstr);
	urhqckem = new CHqcKem(Config.PubKeyTable.at(urID).at("HQC"), nullstr);
	urrqckem = new CRqcKem(Config.PubKeyTable.at(urID).at("RQC"), nullstr);
	urntrukem = new CNtruKem(Config.PubKeyTable.at(urID).at("NTRU"), nullstr);
	urntruprimekem = new CNtruPrimeKem(Config.PubKeyTable.at(urID).at("NTRUPRIME"), nullstr);
	urledakem = new CLedaKem(Config.PubKeyTable.at(urID).at("LEDA"), nullstr);
	urlackem = new CLacKem(Config.PubKeyTable.at(urID).at("LAC"), nullstr);
	ursikekem = new CSikeKem(Config.PubKeyTable.at(urID).at("SIKE"), nullstr);
	urntskem = new CNtsKem(Config.PubKeyTable.at(urID).at("NTS"), nullstr);
	urthreebearskem = new CThreeBearsKem(Config.PubKeyTable.at(urID).at("THREEBEARS"), nullstr);
	urkyberkem = new CKyberKem(Config.PubKeyTable.at(urID).at("KYBER"), nullstr);
	ursaberkem = new CSaberKem(Config.PubKeyTable.at(urID).at("SABER"), nullstr);
	urrollokem = new CRolloKem(Config.PubKeyTable.at(urID).at("ROLLO"), nullstr);
	urround5kem = new CRound5Kem(Config.PubKeyTable.at(urID).at("ROUND5"), nullstr);
	urcmkem = new CCmKem(Config.PubKeyTable.at(urID).at("CM"), nullstr);

//////////////////////////////////////////////////////////////
	CKemTwoWayKep *kemkeps[18] = { new CKemTwoWayKep(myrsakem, urrsakem), new CKemTwoWayKep(mybikekem, urbikekem), new CKemTwoWayKep(myfrodokem, urfrodokem), new CKemTwoWayKep(mynewhopekem,
			urnewhopekem), new CKemTwoWayKep(myhqckem, urhqckem), new CKemTwoWayKep(myrqckem, urrqckem), new CKemTwoWayKep(myntrukem, urntrukem), new CKemTwoWayKep(myntruprimekem, urntruprimekem),
			new CKemTwoWayKep(myledakem, urledakem), new CKemTwoWayKep(mylackem, urlackem), new CKemTwoWayKep(mysikekem, ursikekem), new CKemTwoWayKep(myntskem, urntskem), new CKemTwoWayKep(
					mythreebearskem, urthreebearskem), new CKemTwoWayKep(mykyberkem, urkyberkem), new CKemTwoWayKep(mysaberkem, ursaberkem), new CKemTwoWayKep(myrollokem, urrollokem),
			new CKemTwoWayKep(myround5kem, urround5kem), new CKemTwoWayKep(mycmkem, urcmkem) };

	CDhKep *dhkep = new CDhKep(Config.DH_p, Config.DH_g);

	CTwoWayKep *keps[] = { kemkeps[0], kemkeps[1], kemkeps[2], kemkeps[3], kemkeps[4], kemkeps[5], kemkeps[6], kemkeps[7], dhkep, kemkeps[8], kemkeps[9], kemkeps[10], kemkeps[11], kemkeps[12],
			kemkeps[13], kemkeps[14], kemkeps[15], kemkeps[16], kemkeps[17], dhkep };
	CHybridTwoWayKep *hybridkep = new CHybridTwoWayKep(19, keps);
	CKepPhi *phi = new CKepPhi(hybridkep);
	CKeConn *keconn = new CKeConn(CKeGateWay::Config.ID, urID, phi);

	KeConns.push_back(keconn);

	return 0;
}

int CKeGateWay::InitializePsi(string &urID) {
	CRsaKem *myrsakem, *urrsakem;
	CBikeKem *mybikekem, *urbikekem;
	CFrodoKem *myfrodokem, *urfrodokem;
	CNewHopeKem *mynewhopekem, *urnewhopekem;
	CHqcKem *myhqckem, *urhqckem;
	CRqcKem *myrqckem, *urrqckem;
	CNtruKem *myntrukem, *urntrukem;
	CNtruPrimeKem *myntruprimekem, *urntruprimekem;
	CLedaKem *myledakem, *urledakem;
	CLacKem *mylackem, *urlackem;
	CSikeKem *mysikekem, *ursikekem;
	CNtsKem *myntskem, *urntskem;
	CThreeBearsKem *mythreebearskem, *urthreebearskem;
	CKyberKem *mykyberkem, *urkyberkem;
	CSaberKem *mysaberkem, *ursaberkem;
	CRolloKem *myrollokem, *urrollokem;
	CRound5Kem *myround5kem, *urround5kem;
	CCmKem *mycmkem, *urcmkem;

	string nullstr;

	myrsakem = new CRsaKem(nullstr, Config.PrivKeys.at("RSA"));
	mybikekem = new CBikeKem(nullstr, Config.PrivKeys.at("BIKE"));
	myfrodokem = new CFrodoKem(nullstr, Config.PrivKeys.at("FRODO"));
	mynewhopekem = new CNewHopeKem(nullstr, Config.PrivKeys.at("NEWHOPE"));
	myhqckem = new CHqcKem(nullstr, Config.PrivKeys.at("HQC"));
	myrqckem = new CRqcKem(nullstr, Config.PrivKeys.at("RQC"));
	myntrukem = new CNtruKem(nullstr, Config.PrivKeys.at("NTRU"));
	myntruprimekem = new CNtruPrimeKem(nullstr, Config.PrivKeys.at("NTRUPRIME"));
	myledakem = new CLedaKem(nullstr, Config.PrivKeys.at("LEDA"));
	mylackem = new CLacKem(nullstr, Config.PrivKeys.at("LAC"));
	mysikekem = new CSikeKem(nullstr, Config.PrivKeys.at("SIKE"));
	myntskem = new CNtsKem(nullstr, Config.PrivKeys.at("NTS"));
	mythreebearskem = new CThreeBearsKem(nullstr, Config.PrivKeys.at("THREEBEARS"));
	mykyberkem = new CKyberKem(nullstr, Config.PrivKeys.at("KYBER"));
	mysaberkem = new CSaberKem(nullstr, Config.PrivKeys.at("SABER"));
	myrollokem = new CRolloKem(nullstr, Config.PrivKeys.at("ROLLO"));
	myround5kem = new CRound5Kem(nullstr, Config.PrivKeys.at("ROUND5"));
	mycmkem = new CCmKem(nullstr, Config.PrivKeys.at("CM"));
////////////////////////////////////////////////////////////////////////////////
	urrsakem = new CRsaKem(Config.PubKeyTable.at(urID).at("RSA"), nullstr);
	urbikekem = new CBikeKem(Config.PubKeyTable.at(urID).at("BIKE"), nullstr);
	urfrodokem = new CFrodoKem(Config.PubKeyTable.at(urID).at("FRODO"), nullstr);
	urnewhopekem = new CNewHopeKem(Config.PubKeyTable.at(urID).at("NEWHOPE"), nullstr);
	urhqckem = new CHqcKem(Config.PubKeyTable.at(urID).at("HQC"), nullstr);
	urrqckem = new CRqcKem(Config.PubKeyTable.at(urID).at("RQC"), nullstr);
	urntrukem = new CNtruKem(Config.PubKeyTable.at(urID).at("NTRU"), nullstr);
	urntruprimekem = new CNtruPrimeKem(Config.PubKeyTable.at(urID).at("NTRUPRIME"), nullstr);
	urledakem = new CLedaKem(Config.PubKeyTable.at(urID).at("LEDA"), nullstr);
	urlackem = new CLacKem(Config.PubKeyTable.at(urID).at("LAC"), nullstr);
	ursikekem = new CSikeKem(Config.PubKeyTable.at(urID).at("SIKE"), nullstr);
	urntskem = new CNtsKem(Config.PubKeyTable.at(urID).at("NTS"), nullstr);
	urthreebearskem = new CThreeBearsKem(Config.PubKeyTable.at(urID).at("THREEBEARS"), nullstr);
	urkyberkem = new CKyberKem(Config.PubKeyTable.at(urID).at("KYBER"), nullstr);
	ursaberkem = new CSaberKem(Config.PubKeyTable.at(urID).at("SABER"), nullstr);
	urrollokem = new CRolloKem(Config.PubKeyTable.at(urID).at("ROLLO"), nullstr);
	urround5kem = new CRound5Kem(Config.PubKeyTable.at(urID).at("ROUND5"), nullstr);
	urcmkem = new CCmKem(Config.PubKeyTable.at(urID).at("CM"), nullstr);

//////////////////////////////////////////////////////////////
	CKemTwoWayKep *kemkeps[18] = { new CKemTwoWayKep(myrsakem, urrsakem), new CKemTwoWayKep(mybikekem, urbikekem), new CKemTwoWayKep(myfrodokem, urfrodokem), new CKemTwoWayKep(mynewhopekem,
			urnewhopekem), new CKemTwoWayKep(myhqckem, urhqckem), new CKemTwoWayKep(myrqckem, urrqckem), new CKemTwoWayKep(myntrukem, urntrukem), new CKemTwoWayKep(myntruprimekem, urntruprimekem),
			new CKemTwoWayKep(myledakem, urledakem), new CKemTwoWayKep(mylackem, urlackem), new CKemTwoWayKep(mysikekem, ursikekem), new CKemTwoWayKep(myntskem, urntskem), new CKemTwoWayKep(
					mythreebearskem, urthreebearskem), new CKemTwoWayKep(mykyberkem, urkyberkem), new CKemTwoWayKep(mysaberkem, ursaberkem), new CKemTwoWayKep(myrollokem, urrollokem),
			new CKemTwoWayKep(myround5kem, urround5kem), new CKemTwoWayKep(mycmkem, urcmkem) };

	CDhKep *dhkep = new CDhKep(Config.DH_p, Config.DH_g);

	CTwoWayKep *keps[19];

	int n = 0;

	for (n = 0; n < 18; n++) {
		keps[n] = kemkeps[n];
	}
	//keps[n] = dhkep;

	CKepPsi *psi = new CKepPsi(18, keps);
	CKeConn *keconn = new CKeConn(CKeGateWay::Config.ID, urID, psi);

	KeConns.push_back(keconn);

	return 0;
}

//int CKeGateWay::Iniialize(string &urID)
//{
//	CRsaKem *myrsakem, *urrsakem;
//
//	string nullstr;
//
//	myrsakem = new CRsaKem(nullstr, Config.PrivKeys.at("RSA"));
//
//	urrsakem = new CRsaKem(Config.PubKeyTable.at(urID).at("RSA"), nullstr);
//
//	CKemTwoWayKep *kemkeps[1] =
//	{ new CKemTwoWayKep(myrsakem, urrsakem) };
//	CTwoWayKep *keps[] =
//	{ kemkeps[0] };
//	CHybridTwoWayKep *hybridkep = new CHybridTwoWayKep(1, keps);
//
//	CKeConn *keconn = new CKeConn(OwnID, urID, hybridkep);
//
//	KeConns.push_back(keconn);
//
//	return 0;
//}

//int CKeGateWay::Iniialize(string &urID)
//{
//	CBikeKem *mybikekem, *urbikekem;
//
//	string nullstr;
//
//	mybikekem = new CBikeKem(nullstr, Config.PrivKeys.at("BIKE"));
//
//	urbikekem = new CBikeKem(Config.PubKeyTable.at(urID).at("BIKE"), nullstr);
//
//	CKemTwoWayKep *kemkeps[1] =
//	{ new CKemTwoWayKep(mybikekem, urbikekem) };
//	CTwoWayKep *keps[] =
//	{ kemkeps[0] };
//	CHybridTwoWayKep *hybridkep = new CHybridTwoWayKep(1, keps);
//
//	CKeConn *keconn = new CKeConn(OwnID, urID, hybridkep);
//
//	KeConns.push_back(keconn);
//
//	return 0;
//}

void* CKeGateWay::TCPServer(void *arg) {
	CTcpComm::SerArg args, *pargs = (CTcpComm::SerArg*) arg;

	args.IPaddr = pargs->IPaddr;
	args.port = pargs->port;
	args.callback = pargs->callback;
	args.Socketfd = pargs->Socketfd;

	delete pargs;

	*args.Socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in serv_addr;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr((char*) args.IPaddr.c_str());
	serv_addr.sin_port = htons(args.port);

	bind(*args.Socketfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	listen(*args.Socketfd, 10);
	printf("TCP Listen at: %s:%d\n", args.IPaddr.c_str(), args.port);

	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);

	while (1) {
		int fp = accept(*args.Socketfd, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
		cout << "=======================================================================================" << endl;
		cout << "Received a Key Exchange request" << endl;
		cout << "fd = " << fp << endl;
		cout << "received data" << endl;

		args.callback(fp);

		close(fp);
	}

	return NULL;
}

#define BUFF_LEN 1024
void* CKeGateWay::LocalUDPServer(void *arg) {
	unsigned char buf[BUFF_LEN];
	socklen_t len;
	int count;
	struct sockaddr_in client_addr;  //clent_addr用于记录发送方的地址信息
	int server_fd, ret;
	struct sockaddr_in ser_addr;
	string SS;
	char sessionID[65], userID[65];

	server_fd = socket(AF_INET, SOCK_DGRAM, 0); //AF_INET:IPV4;SOCK_DGRAM:UDP
	if (server_fd < 0) {
		printf("create UDP socket fail!\n");
		return NULL;
	}
	CKeGateWay::UDPSerSocket = server_fd;

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
	ser_addr.sin_port = htons(9527);  //端口号，需要网络序转换

	ret = bind(server_fd, (struct sockaddr*) &ser_addr, sizeof(ser_addr));
	if (ret < 0) {
		printf("UDP socket bind fail!\n");
		return NULL;
	}
	printf("UDP server started up at 0.0.0.0:9527\n");
	printf("Mode: %d, Role: %d\n", CKeGateWay::Config.Mode, CKeGateWay::Config.Role);
	while (1) {
		memset(buf, 0, BUFF_LEN);
		len = sizeof(client_addr);
		if ((count = recvfrom(server_fd, buf, BUFF_LEN, 0, (struct sockaddr*) &client_addr, &len)) < 0) {
			printf("UDP socket recieve data fail! errno: %d\n", errno);
			continue;
		}
		cout << "UDP received data, size: " << count << endl;
		if (count != 128) {
			cout << "UDP received data length error!" << endl;
			continue;
		}
		memset(sessionID, 0, 65);
		memset(userID, 0, 65);
		memcpy(sessionID, buf, 64);
		memcpy(userID, buf + 64, 64);
		if (CKeGateWay::Config.Mode == GATEWAY_MODE_CS) {
			if (CKeGateWay::Config.Role == GATEWAY_ROLE_CLIENT) {
				printf("UDP request user ID: %s\n", userID);
				printf("UDP request Session ID: %s\n", sessionID);
				CKeGateWay::ShareWith((char*) CKeGateWay::Config.ServerID.c_str(), (char*) sessionID, SS);
				memset(buf, 0, BUFF_LEN);
				memcpy(buf, SS.data(), SS.length());
				sendto(server_fd, buf, SS.length(), 0, (struct sockaddr*) &client_addr, len);
			} else {
				printf("UDP request User ID: %s\n", userID);
				printf("UDP request Session ID: %s\n", sessionID);
				CKeConn *keconn = CKeGateWay::GetKeConn(userID);
				string sessID((char*) sessionID), SS;

				SS = keconn->WaitNewSS(sessID);
				memset(buf, 0, BUFF_LEN);
				if (keconn == NULL) {
					printf("============================ Device NOT Found\n");
					sendto(server_fd, buf, 32, 0, (struct sockaddr*) &client_addr, len);
				} else {
					cout << "Found SS: " << CSerializable::Str2Hex(keconn->SS) << endl;
					memcpy(buf, SS.data(), SS.length());
					sendto(server_fd, buf, SS.length(), 0, (struct sockaddr*) &client_addr, len);
				}
			}

		} else {

		}

	}
	return NULL;
}
