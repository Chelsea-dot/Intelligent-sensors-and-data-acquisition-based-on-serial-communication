#ifndef __NIOSERVICE_WORKSTATION_H__
#define __NIOSERVICE_WORKSTATION_H__
#include<winsock2.h>
#include<stdio.h>
# define BUFFER_SIZE  1024    //缓冲区大小

class NioService {
private:
	SOCKET sock_Client;
	SOCKADDR_IN addr_server;
	SOCKADDR_IN sock;
	int len;
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
		printf("初始化失败!");
	}
	sock_Client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//创建客户端用于通信的Socket
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(4567);
	addr_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	len = sizeof(sock);
}

NioService::~NioService() {};

void NioService::close() {
	closesocket(sock_Client);
	WSACleanup();
}

void NioService::send(char* buf) {
	sendto(sock_Client, buf, strlen(buf), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
}

int NioService::recv(char* buf) {
	int last = recvfrom(sock_Client, buf, 1024, 0, (SOCKADDR*)&sock, &len);
	return last;
}

#endif
