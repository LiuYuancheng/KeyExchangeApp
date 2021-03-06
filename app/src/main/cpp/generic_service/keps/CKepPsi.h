/*
 * CKepPsi.h
 *
 *  Created on: 21 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CKEPPSI_H_
#define CPP_CKEPPSI_H_
#include <openssl/bio.h>
#include <openssl/sha.h>
//#include <glog/logging.h>

#include "../../generic_service/lower_keps/CHybridTwoWayKep.h"
#include "../../generic_service/lower_keps/CTwoWayKep.h"
#include "../../include/pqch_kdf.h"
#include "../debug_config.h"
#include "CAppKep.h"

#define MSG_TYPE_INIT 			0x00
#define MSG_TYPE_CONF			0x10
#define MSG_TYPE_VRFY			0x20
#define MSG_TYPE_SHARE			0x01
#define MSG_TYPE_RESET 			0x02
#define MSG_TYPE_FINAL 			0x03
#define MSG_TYPE_KEX			0x30
#define MSG_TYPE_RST			0x40
#define MSG_TYPE_SETUP			0x50

class CKepPsi: public CHybridTwoWayKep {
public:

private:
	int StateIndicator;

#define SYN_STATE_INITIAL 			0x00
#define SYN_STATE_INITIALIZED		0x01
	int SyncState;

public:
	CKepPsi(int count, CTwoWayKep *keps[]);
	virtual ~CKepPsi();

private:
	int Kdf() {
		unsigned char *s = new unsigned char[SharedStr.length()];

		PQCH_KDF_M257pX_SHA256((unsigned char*) SharedStr.data(), SharedStr.length(), s, (unsigned char*) TwoWayKeps[StateIndicator - 1]->SharedStr.data(),
				TwoWayKeps[StateIndicator - 1]->SharedStr.size());

		string temp((char*) s, 32);

		delete[] s;
		this->SharedStr = temp;

		return 0;
	}

public:

	int Setup(CComm *comm) {
		string data;
		size_t len;
		int type, state;

		this->Keypair();
		this->SetupRequest(comm);

		data = comm->Recv(sizeof(char));
		type = (int) CSerializable::Str2Ch(data);
		data = comm->Recv(sizeof(char));
		state = (int) CSerializable::Str2Ch(data);

		if (MSG_TYPE_INIT != type) {
			cout << "unexpected message type: " << type << endl;

			return -1;
		}
		this->OnInitialResponse(comm);

		data = comm->Recv(sizeof(char));
		type = (int) CSerializable::Str2Ch(data);

		if (type == MSG_TYPE_VRFY) {
			if (0 == this->OnVerifying(comm)) {
				this->SyncState = SYN_STATE_INITIALIZED;
				this->UpdateStateIndicator();
				cout << "initialized ..." << endl;
			}
		} else {
			cout << "unexpected message!" << endl;

			return -1;
		}

		return 0;
	}

	int DoKe(CComm *comm) {
		string data;
		size_t len;
		int type, state;

		tag:

		if (this->SyncState == SYN_STATE_INITIAL) {
			this->Keypair();
			this->InitialRequest(comm);

			data = comm->Recv(sizeof(char));
			type = (int) CSerializable::Str2Ch(data);
			data = comm->Recv(sizeof(char));
			state = (int) CSerializable::Str2Ch(data);

			if (MSG_TYPE_INIT != type) {
				cout << "unexpected message type: " << type << endl;

				return -1;
			}
			this->OnInitialResponse(comm);

			data = comm->Recv(sizeof(char));
			type = (int) CSerializable::Str2Ch(data);

			if (type == MSG_TYPE_VRFY) {
				if (0 == this->OnVerifying(comm)) {
					this->SyncState = SYN_STATE_INITIALIZED;
					this->UpdateStateIndicator();
					cout << "initialized ..." << endl;
				}
			} else {
				cout << "unexpected message!" << endl;

				return -1;
			}
		}
		if (this->SyncState == SYN_STATE_INITIALIZED) {
			this->Keypair();
			this->KexRequest(comm);

			data = comm->Recv(sizeof(char));
			type = (int) CSerializable::Str2Ch(data);
			data = comm->Recv(sizeof(char));
			state = (int) CSerializable::Str2Ch(data);

			if (MSG_TYPE_INIT != type) {
				cout << "unexpected message type: " << type << endl;

				if (MSG_TYPE_RST == type) {
					this->SyncState = SYN_STATE_INITIAL;
					this->StateIndicator = 0;

					cout << "Resetting ..." << endl;

					goto tag;

				}
				return -1;
			}

			this->OnKexResponse(comm);

			data = comm->Recv(sizeof(char));
			type = (int) CSerializable::Str2Ch(data);

			if (type == MSG_TYPE_VRFY) {
				if (0 == this->OnVerifying(comm)) {
					this->UpdateStateIndicator();
					cout << "shared ..." << endl;
				}
			} else {
				cout << "unexpected message!" << endl;

				return -1;
			}

		}

		return 0;
	}

	int OnKe(CComm *comm) {
		string data;
		size_t len;
		int type, type0, state;

		tag:

		data = comm->Recv(sizeof(char));
		type = (int) CSerializable::Str2Ch(data);
		data = comm->Recv(sizeof(char));
		state = (int) CSerializable::Str2Ch(data);

		type0 = type;

		switch (type) {
		case MSG_TYPE_SETUP:
		case MSG_TYPE_INIT:

			if (this->SyncState != SYN_STATE_INITIAL) {
				this->SyncState = SYN_STATE_INITIAL;
				this->StateIndicator = 0;
			}
			this->OnInitialRequest(comm);

			data = comm->Recv(sizeof(char));
			if (data.length() == 0) {
				cout << "===============================" << errno << endl;
			}
			type = CSerializable::Str2Ch(data);

			if (MSG_TYPE_CONF != type) {
				cout << "unexpected message! 1" << endl;

				return -1;
			}

			if (0 == this->OnConfirming(comm)) {
				this->SyncState = SYN_STATE_INITIALIZED;
				this->UpdateStateIndicator();
				cout << "initialized ..." << endl;
			}

			printf("========== type: %d\n", type0);
			if (type0 == MSG_TYPE_SETUP) {
				break;
			}
			data = comm->Recv(sizeof(char));
			type = (int) CSerializable::Str2Ch(data);
			data = comm->Recv(sizeof(char));
			state = (int) CSerializable::Str2Ch(data);

			;
			;
		case MSG_TYPE_KEX:
			if (this->SyncState != SYN_STATE_INITIALIZED) {
				cout << "unexpected message! 2" << endl;
				this->SyncState = SYN_STATE_INITIAL;
				this->StateIndicator = 0;

				this->DropData(comm);
				this->ResetRequest(comm);

				goto tag;
			}
			this->OnKexRequest(comm);

			data = comm->Recv(sizeof(char));
			type = CSerializable::Str2Ch(data);

			if (MSG_TYPE_CONF != type) {
				cout << "unexpected message! 3" << endl;

				return -1;
			}

			if (0 == this->OnConfirming(comm)) {
				this->UpdateStateIndicator();
				cout << "shared ..." << endl;
			}
			break;

		default:
			;
		}

		return 0;

	}

private:

	int SetupRequest(CComm *comm) {
		string data;

		data = CSerializable::Ch2Str((char) MSG_TYPE_SETUP) + CSerializable::Ch2Str((char) StateIndicator) + CHybridTwoWayKep::Serialize();

		cout << "=========================" << endl;
		if (comm->Send(data)) {
			cout << "Send error" << endl;
			return -1;
		}

		cout << "data sent ... " << data.length() << " bytes." << endl;

		return 0;
	}

	int InitialRequest(CComm *comm) {
		string data;

		data = CSerializable::Ch2Str((char) MSG_TYPE_INIT) + CSerializable::Ch2Str((char) StateIndicator) + CHybridTwoWayKep::Serialize();

		cout << "=========================" << endl;
		if (comm->Send(data)) {
			cout << "Send error" << endl;
			return -1;
		}

		cout << "data sent ... " << data.length() << " bytes." << endl;

		return 0;
	}

	int KexRequest(CComm *comm) {
		string data;

		data = CSerializable::Ch2Str((char) MSG_TYPE_KEX) + CSerializable::Ch2Str((char) StateIndicator) + this->TwoWayKeps[(StateIndicator - 1) % this->TwoWayKeps.size()]->Serialize();

		if (comm->Send(data))
			return -1;

		cout << "KEX sent ... " << data.length() << " bytes." << endl;

		return 0;
	}

	int ResetRequest(CComm *comm) {
		string data;

		data = CSerializable::Ch2Str((char) MSG_TYPE_RST) + CSerializable::Ch2Str((char) StateIndicator);

		if (comm->Send(data))
			return -1;

		cout << "RST sent ... " << data.length() << " bytes." << endl;

		return 0;
	}

	int OnInitialResponse(CComm *comm) {
		string data;
		size_t len = 0;

		data = comm->Recv(sizeof(size_t));

		len = CSerializable::Str2ULL(data);
		data = comm->Recv(len);

		CHybridTwoWayKep::Deserlize(data);

		this->Compute();

		cout << "Shared :" << endl;
		BIO_dump_fp(stdout, this->SharedStr.data(), this->SharedStr.size());

		return 0;
	}

	int OnKexResponse(CComm *comm) {
		string data;
		size_t len = 0;
		int idx;

		data = comm->Recv(sizeof(size_t));

		len = CSerializable::Str2ULL(data);
		data = comm->Recv(len);

		idx = (this->StateIndicator - 1) % this->TwoWayKeps.size();
		((CTwoWayKep*) this->TwoWayKeps[idx])->Deserlize(data);

		this->Compute();

		cout << "Shared :" << endl;
		BIO_dump_fp(stdout, this->SharedStr.data(), this->SharedStr.size());

		return 0;
	}

	int OnInitialRequest(CComm *comm) {
		string data;
		size_t len = 0;

		data = comm->Recv(sizeof(size_t));

		len = CSerializable::Str2ULL(data);
		data = comm->Recv(len);

		CHybridTwoWayKep::Deserlize(data);

		this->Keypair();
		this->Compute();

		cout << "Shared :" << endl;
		BIO_dump_fp(stdout, this->SharedStr.data(), this->SharedStr.size());

		this->InitialResponse(comm);
		this->Verify(comm);

		return 0;

	}

	int OnKexRequest(CComm *comm) {
		string data;
		size_t len = 0;
		int idx;

		data = comm->Recv(sizeof(size_t));

		len = CSerializable::Str2ULL(data);
		data = comm->Recv(len);

		idx = (this->StateIndicator - 1) % this->TwoWayKeps.size();

		((CTwoWayKep*) (this->TwoWayKeps[idx]))->Deserlize(data);

		this->Keypair();
		this->Compute();

		cout << "Shared :" << endl;
		BIO_dump_fp(stdout, this->SharedStr.data(), this->SharedStr.size());

		this->KexResponse(comm);
		this->Verify(comm);

		return 0;

	}

	int InitialResponse(CComm *comm) {
		cout << "=============" << endl;
		string data = CSerializable::Ch2Str((char) MSG_TYPE_INIT) + CSerializable::Ch2Str((char) StateIndicator) + CHybridTwoWayKep::Serialize();

		if (comm->Send(data))
			return -1;

		cout << "data sent ... " << data.length() << " bytes." << endl;

		return 0;

	}

	int KexResponse(CComm *comm) {
		cout << "=============" << endl;

		int idx = (StateIndicator - 1) % this->TwoWayKeps.size();

		string data = CSerializable::Ch2Str((char) MSG_TYPE_INIT) + CSerializable::Ch2Str((char) StateIndicator) + ((CTwoWayKep*) this->TwoWayKeps[idx])->Serialize();

		if (comm->Send(data))
			return -1;

		cout << "KEX sent ... " << data.length() << " bytes." << endl;

		return 0;

	}

	int Verify(CComm *comm) {
		unsigned char digest[32];

		SHA256((unsigned char*) this->SharedStr.data(), this->SharedStr.size(), digest);
		cout << "generated " << 32 << " bytes digest: " << endl;
		BIO_dump_fp(stdout, digest, 32);

		string data((char*) digest, 32);
		data = CSerializable::ULL2Str((size_t) 32) + data;
		data = CSerializable::Ch2Str(MSG_TYPE_VRFY) + data;

		if (comm->Send(data))
			return -1;

		cout << "Verification sent ... " << data.size() << " bytes." << endl;

		return 0;
	}

	int OnVerifying(CComm *comm) {
		unsigned char digest[32];
		string data;
		size_t len;

		data = comm->Recv(sizeof(size_t));
		len = CSerializable::Str2ULL(data);
		data = comm->Recv(len);

		SHA256((unsigned char*) this->SharedStr.data(), this->SharedStr.size(), digest);

		cout << "generated " << 32 << " bytes digest: " << endl;
		BIO_dump_fp(stdout, digest, 32);

		if (memcmp(digest, data.data(), 32)) {
			this->Disagree(comm);

			return -1;
		}
		this->Agree(comm);

		return 0;
	}

	int Agree(CComm *comm) {
		string data;

		data = CSerializable::Ch2Str((char) MSG_TYPE_CONF) + CSerializable::Ch2Str((char) 0x01);

		if (comm->Send(data))
			return -1;

		cout << "Confirmation sent ... " << data.length() << " bytes." << endl;

		return 0;
	}

	int Disagree(CComm *comm) {
		string data;

		data = CSerializable::Ch2Str((char) MSG_TYPE_CONF) + CSerializable::Ch2Str((char) 0x00);

		if (comm->Send(data))
			return -1;

		cout << "Confirmation sent ... " << data.length() << " bytes." << endl;

		return 0;
	}

	int OnConfirming(CComm *comm) {
		string data;
		int result;

		data = comm->Recv(sizeof(char));
		result = CSerializable::Str2Ch(data);

		if (0x01 == result) {
			return 0;
		}

		return -1;
	}

	inline void UpdateStateIndicator() {
		StateIndicator = (StateIndicator + 1) % (TwoWayKeps.size() + 1);
		if (StateIndicator == 0) {
			StateIndicator++;
		}
		printf("state updated to %d\n", StateIndicator);
	}

	int DropData(CComm *comm) {
		string data;
		size_t len = 0;
		int idx;

		data = comm->Recv(sizeof(size_t));

		len = CSerializable::Str2ULL(data);
		comm->Recv(len);

		return 0;

	}

	int Keypair() {
		int idx;

		cout << "\n\nINFO: Starting KEP, State = " << StateIndicator << " Size: " << TwoWayKeps.size() << endl;

		if (StateIndicator == 0) {
#ifdef PRINT_DATA
			cout << "Psi Keypair, Internal state: " << StateIndicator << endl;
#endif
			CHybridTwoWayKep::Keypair();
		} else {
#ifdef PRINT_DATA
			cout << "Psi Keypair, Internal state: " << StateIndicator << endl;
#endif
			idx = (StateIndicator - 1) % this->TwoWayKeps.size();
			((CTwoWayKep*) this->TwoWayKeps[idx])->Keypair();
#ifdef PRINT_DATA
			cout << "KEP Name: " << ((CTwoWayKep*) this->TwoWayKeps[idx])->KepName << endl;
			/*			string newPub = ((CTwoWayKep*) this->TwoWayKeps[idx])->Pub;
			 cout << "Own Pub:" << endl;
			 BIO_dump_fp(stdout, newPub.data(), newPub.length());*/
#endif
		}

		return 0;

	}

	int Compute() {
		cout << "INFO: Ending KEP, State = " << StateIndicator << " Size: " << TwoWayKeps.size() << endl;

		if (StateIndicator == 0) {
			CHybridTwoWayKep::Compute();
		} else {
			this->SharedStr.clear();

			for (int i = 0; i < TwoWayKeps.size(); i++) {
				if (StateIndicator - 1 == i) {
					((CTwoWayKep*) TwoWayKeps[i])->Compute();
#ifdef PRINT_DATA
					/*					string newPub = ((CTwoWayKep*) TwoWayKeps[i])->PubCp;
					 cout << "i = " << i << endl;
					 cout << "Peer Pub:" << endl;
					 BIO_dump_fp(stdout, newPub.data(), newPub.length());*/
#endif
				}
				this->SharedStr = this->SharedStr + ((CTwoWayKep*) TwoWayKeps[i])->SharedStr;
			}
			this->Kdf();

		}
		cout << "INFO: Finished KEP,  State = " << StateIndicator << " Size: " << TwoWayKeps.size() << endl;

		return 0;
	}

private:

	string HashInternalState() {
		string internalState = "";
		unsigned char digest[32];

		vector<CTwoWayKep*> *keps = &this->TwoWayKeps;
		vector<CTwoWayKep*>::iterator it;

		for (it = keps->begin(); it != keps->end(); it++) {
			internalState += (*it)->Priv;
			//	BIO_dump_fp(stdout, (*it)->Priv.data(), (*it)->Priv.length());

		}
		internalState += CSerializable::ULL2Str(this->StateIndicator);
		//	BIO_dump_fp(stdout, internalState.data(), internalState.length());

		SHA256((const unsigned char*) internalState.data(), (size_t) internalState.size(), digest);

		string hashedState((char*) digest);

		return hashedState;

	}

	bool CheckInternalState(string &remoteState) {
		string localState = HashInternalState();

		if (localState == remoteState) {
			return true;
		}
		return true;
	}
};

#endif /* CPP_CKEPPSI_H_ */
