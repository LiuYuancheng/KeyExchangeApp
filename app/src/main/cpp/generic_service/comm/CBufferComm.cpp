/*
 * CTcpComm.cpp
 *
 *  Created on: 23 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/comm/CBufferComm.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

using namespace std;

int CTcpComm::OppSocket = 0;
string CTcpComm::SocketAddr;


CBufferComm::CBufferComm(string &ipaddr, int port, void (*callback)())
{
	SerSocket = 0;

	pthread_t tidp;
	CTcpComm::SerArg *arg = new CTcpComm::SerArg;

	arg->IPaddr = ipaddr;
	arg->port = port;
	arg->callback = callback;
	arg->Socketfd = &SerSocket;

	if ((pthread_create(&tidp, NULL, CTcpComm::Server, (void*) arg)) == -1)
	{
		printf("create error!\n");
	}

}

CBufferComm::~CBufferComm()
{
	close(SerSocket);
}

int CBufferComm::Client()
{

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(
			(char*) CTcpComm::GetSocketAddrIP().c_str());
	serv_addr.sin_port = htons(CTcpComm::GetSocketAddrPort());

	int tcpMaxSeg = 1000;

	setsockopt(sock, IPPROTO_TCP, TCP_MAXSEG, &tcpMaxSeg, sizeof(tcpMaxSeg));
	connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

	CTcpComm::OppSocket = sock;

	return sock;
}

void* CBufferComm::Server(void *arg)
{
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

	while (1)
	{
		int fp = accept(*args.Socketfd, (struct sockaddr*) &clnt_addr,
				&clnt_addr_size);

		cout << "fd = " << fp << endl;
		CTcpComm::OppSocket = fp;
		cout << "received data" << endl;

		args.callback();
	}

	return NULL;
}

int CBufferComm::Send(string &data)
{

	cout << "INFO: Sending to " << CTcpComm::SocketAddr << endl;

	size_t m = this->Write(CTcpComm::OppSocket, data);

	cout << "INFO: TCP written: " << m << " bytes" << endl;
	cout << "INFO: DST address: " << CTcpComm::SocketAddr << endl;

	return 0;
}

string CBufferComm::Recv(size_t nbytes)
{
	cout << "Received data from fp = " << CTcpComm::OppSocket << endl;
	return this->Read(CTcpComm::OppSocket, nbytes);
}

size_t CBufferComm::Write(int fd, string &data)
{
	int nLeft, nWrite, nTotalWrite = 0;
	unsigned char *p;

	p = (unsigned char*) data.data();
	nLeft = data.size();

	while (nLeft > 0)
	{
		if ((nWrite = write(fd, p, nLeft)) <= 0)
		{
			nWrite = 0;
		}
		nLeft -= nWrite;
		p += nWrite;
		nTotalWrite += nWrite;
	}
	return nTotalWrite;
}

string CBufferComm::Read(int fd, size_t nbytes)
{
	size_t nLeft, nRead, nTotalRead = 0;
	unsigned char *buf, *p;
	p = buf = new unsigned char[nbytes];

	nLeft = nbytes;

	while (nLeft > 0)
	{
		if ((nRead = read(fd, p, nLeft)) < 0)
		{
			nRead = 0;
		}
		else if (nRead == 0)
		{
			goto exit;
		}

		nLeft -= nRead;
		p += nRead;
		nTotalRead += nRead;
	}

	cout << "&&&&&&&&&&&&&&&&&&&" << nTotalRead << "======" << nbytes << endl;

	if (nTotalRead != nbytes)
	{
		string str;

		cout << "Read Corrupted" << endl;
		delete[] buf;

		return str;
	}
	else
	{
		string str((char*) buf, nbytes);

		delete[] buf;

		return str;
	}
	exit: delete[] buf;
	string str;
	return str;

}

