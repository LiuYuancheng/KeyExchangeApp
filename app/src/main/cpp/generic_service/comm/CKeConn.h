/*
 * CKeConn.h
 *
 *  Created on: 22 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CKECONN_H_
#define CPP_CKECONN_H_

#include <iostream>
#include <string>

using namespace std;

#include "../../generic_service/CSerializable.h"
#include "../../generic_service/lower_keps/CTwoWayKep.h"
#include "../../generic_service/comm/CComm.h"
#include "../comm/CComm.h"
#include "../keps/CAppKep.h"
#include "hybrid_kem.h"

class CKeConn: CSerializable {
public:
	CKep *Kep;

	string SrcID;
	string DstID;

	string peerIP;

	string OldSessionID;
	string OldSS;

	string SessionID;
	string SS;
private:
	pthread_mutex_t lock;

	void Lock() {
		pthread_mutex_lock(&this->lock);
	}
	void Unlock() {
		pthread_mutex_unlock(&this->lock);
	}

public:
	CKeConn(string &srcid, string &distid, CKep *kep);
	virtual ~CKeConn();

	string Share(CComm *conn, char *sessionID) {
		string ret("");
		string header;
		string sessID;

		this->Lock();
		if (sessionID) {
			sessID.append(sessionID);
		} else {
			sessID.append("0000000000000000000000000000000000000000000000000000000000000000");
		}
		header = CSerializable::ULL2Str(SrcID.size()) + SrcID + CSerializable::ULL2Str(DstID.size()) + DstID + CSerializable::ULL2Str(sessID.size()) + sessID;

		cout << "Sending the header ..., Size: " << header.size() << endl;
		cout << SrcID << " => " << DstID << endl;
		conn->Send(header);
		cout << "Sent the header." << endl;

		if (sessionID) { // sessionID must be NULL if setup is to be conducted.
			Kep->DoKe(conn);
			this->OldSessionID = this->SessionID;
			this->OldSS = this->SS;
			this->SessionID = sessID;
			ret = this->SS = Kep->SharedStr;
			cout << "Session set." << endl;
			cout << "Session ID: " << this->SessionID << endl;
			cout << "Shared Secret: " << CSerializable::Str2Hex(this->SS) << endl;

		} else {
			Kep->Setup(conn);
		}
		this->Unlock();

		return ret;
	}

	string OnSharing(CComm *conn, char *sessionID) {
		this->Lock();
		Kep->OnKe(conn);
		this->OldSessionID = this->SessionID;
		this->SessionID = sessionID;
		this->OldSS = this->SS;
		this->SS = Kep->SharedStr;
		this->Unlock();

		return this->SS;
	}

	string WaitNewSS(string &sessionID) {
		string ret;

		while (1) {
			this->Lock();
			if (this->SessionID != sessionID) {
				this->Unlock();
				continue;
			}
			ret = this->SS;
			this->Unlock();
			break;
		}
		return ret;
	}

public:
	/* ISerializable implemented methods*/
	string Serialize() {

		return "";

	}

	void Deserlize(string &str) {

	}

	void Request();

};

#endif /* CPP_CKECONN_H_ */

