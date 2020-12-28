/*
 * CTcpComm.h
 *
 *  Created on: 23 Feb 2020
 *      Author: yiwen
 */

#ifndef CPP_CBUFFERCOMM_H_
#define CPP_CBUFFERCOMM_H_


#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

#include "../../generic_service/comm/CComm.h"

class CBufferComm: public CComm
{
public:

	unsigned char * buffer;


public:
	CBufferComm()
	{

	}
	CBufferComm(string &ipaddr, int port, void (*callback)());
	virtual ~CTcpComm();

	int Send(string &data);

	string Recv(size_t nbytes);

	void SetSendAddr(string &addr)
	{
		CTcpComm::SocketAddr = addr;
	}
private:
	size_t Write(int fd, string &data);

	string Read(int fd, size_t nbytes);

public:
	static string GetSocketAddrIP()
	{
		size_t pos = CTcpComm::SocketAddr.find_first_of(':');
		return CTcpComm::SocketAddr.substr(0, pos);
	}
	static int GetSocketAddrPort()
	{
		size_t pos = CTcpComm::SocketAddr.find_first_of(':');
		return atoi(
				CTcpComm::SocketAddr.substr(pos + 1,
						CTcpComm::SocketAddr.size()).c_str());
	}

	static int Client();
	static int RmClient()
	{
		close(CTcpComm::OppSocket);
		return 0;
	}

	static void* Server(void *arg);

	struct SerArg
	{
		string IPaddr;
		int port;
		void (*callback)();
		int *Socketfd;
	};

};

#endif /* CPP_CTCPCOMM_H_ */
