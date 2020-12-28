/*
 * test_client1.c
 *
 *  Created on: 23 Apr 2020
 *      Author: yiwen
 */
#include <inttypes.h>
#include <openssl/bio.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 9527
#define BUFF_LEN 1024

int main(int argc, char *argv[]) {
	int client_fd;
	struct sockaddr_in src;
	struct sockaddr_in ser_addr;
	unsigned char buf[BUFF_LEN];
	socklen_t len;
	size_t count;
	char sessionID[64] = "1234567890";

	client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (client_fd < 0) {
		printf("create socket fail!\n");
		return -1;
	}

	memset(&ser_addr, 0, sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	//ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(SERVER_PORT);

	memcpy(buf, sessionID, 64);
	sendto(client_fd, buf, BUFF_LEN, 0, (struct sockaddr*) &ser_addr, sizeof(ser_addr));
	memset(buf, 0, BUFF_LEN);
	if ((count = recvfrom(client_fd, buf, BUFF_LEN, 0, (struct sockaddr*) &src, &len)) < 0) {
		close(client_fd);
		return -1;
	}

	close(client_fd);

	for (int i = 0; i < count; i++)
		printf("%02x", buf[i]);
	printf("\n");

}

