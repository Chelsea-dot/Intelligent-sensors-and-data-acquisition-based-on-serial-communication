#ifndef __NIOSERVICE_SENSOR_H__
#define __NIOSERVICE_SENSOR_H__
#include<winsock2.h>
#include<stdio.h>
#define BUFFER_SIZE  1024    //缓冲区大小

class NioService {
private:
	int fromlen;
	char cmd[BUFFER_SIZE];
	SOCKET sockServer;
	SOCKADDR_IN addr_Server;
	SOCKADDR_IN addr_Clt;

public:
	NioService();
	~NioService();
	void close();
	void send(char* buf);
	int recv(char* buf);
};

NioService::NioService() {
	WSADATA WSAData;

	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		printf("初始化失败");
		exit(1);
	}
	sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockServer == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
	}

	addr_Server.sin_family = AF_INET;
	addr_Server.sin_port = htons(4567);
	addr_Server.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(sockServer, (SOCKADDR*)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR) {//服务器与本地地址绑定
		printf("Failed socket() %d \n", WSAGetLastError());
	}
	fromlen = sizeof(SOCKADDR);
}

NioService::~NioService() {};

void NioService::close() {
	closesocket(sockServer);
	WSACleanup();
}

void NioService::send(char* buf) {
	sendto(sockServer, buf, strlen(buf), 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR));
}

int NioService::recv(char* buf) {
	int last = recvfrom(sockServer, buf, sizeof(buf), 0, (SOCKADDR*)&addr_Clt, &fromlen);
	return last;
}

#endif