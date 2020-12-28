/*
 * CTcpComm.cpp
 *
 *  Created on: 23 Feb 2020
 *      Author: yiwen
 */

#include "../../generic_service/comm/CTcpComm.h"

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <glog/logging.h>

#include <iostream>

using namespace std;

/*int CTcpComm::OppSocket = 0;
 string CTcpComm::SocketAddr;


 CTcpComm::CTcpComm(string &ipaddr, int port, void (*callback)())
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

 CTcpComm::~CTcpComm()
 {
 close(SerSocket);
 }
 */
int CTcpComm::Connect(char *IPaddr, int port) {

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	int ret;
	struct sockaddr_in serv_addr;
	int tcpMaxSeg = 1000;
	struct timeval tval;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(IPaddr);
	serv_addr.sin_port = htons(port);

	setsockopt(sock, IPPROTO_TCP, TCP_MAXSEG, &tcpMaxSeg, sizeof(tcpMaxSeg));
	tval.tv_sec = 10;
	setsockopt(sock, IPPROTO_TCP, SO_RCVTIMEO, &tval, sizeof(tval));

	ret = connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	if (ret < 0) {
		return ret;
	}
	return sock;
}

void CTcpComm::Reset() {
	close(fd);
}

/*
 void* CTcpComm::Server(void *arg)
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

 close(fp);
 }

 return NULL;
 }
 */

int CTcpComm::Send(string &data) {
	cout << "fd: " << this->fd << endl;

	size_t m = this->Write(this->fd, data), m0;

	cout << "INFO: Written: " << m << " bytes." << endl;

	if ((m0 = data.length()) != m) {
		printf("Send: Written %d/%d\n", m0, m);
		return -1;
	}
	return 0;
}

string CTcpComm::Recv(size_t nbytes) {
	string str = this->Read(this->fd, nbytes);

	cout << "INFO: Read " << str.size() << " bytes" << endl;

	return str;
}

size_t CTcpComm::Write(int fd, string &data) {
	int nLeft, nWrite, nTotalWrite = 0;
	unsigned char *p;

	p = (unsigned char*) data.data();
	nLeft = data.size();

	while (nLeft > 0) {
		if ((nWrite = write(fd, p, nLeft)) <= 0) {
			LOG(INFO) << "Socket write error, errno: " << errno;
			if (errno == ETIME) {
				LOG(INFO) << "Socket write timeout.";
			}
			nWrite = 0;
		}
		nLeft -= nWrite;
		p += nWrite;
		nTotalWrite += nWrite;
	}
	return nTotalWrite;
}

string CTcpComm::Read(int fd, size_t nbytes) {
	size_t nLeft, nRead, nTotalRead = 0;
	unsigned char *buf, *p;
	p = buf = new unsigned char[nbytes];

	nLeft = nbytes;

	while (nLeft > 0) {
		if ((nRead = read(fd, p, nLeft)) <= 0) {
			goto exit;
		}
		nLeft -= nRead;
		p += nRead;
		nTotalRead += nRead;
	}

//	cout << "&&&&&&&&&&&&&&&&&&&" << nTotalRead << "======" << nbytes << endl;

	if (nTotalRead != nbytes) {
		string str;

		cout << "Read Corrupted" << endl;
		delete[] buf;

		return str;
	} else {
		string str((char*) buf, nbytes);

		delete[] buf;

		return str;
	}
	exit: delete[] buf;
	string str;
	return str;

}

