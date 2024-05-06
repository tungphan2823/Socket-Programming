#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include  <stdio.h>
#include <WinSock2.h>

void quit(const char* msg) {
	printf("Error: %s\n", msg);
	exit(1);
}
int main(int argc, char** argv) {
	if (argc != 3) quit("Command argument problem"); //THis is client also need server's IP
	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w);
	if (ret == 1)quit("Winsock API");
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == SOCKET_ERROR) quit("Create SOCKET");
	printf("Socket is Ready\n");
	SOCKADDR_IN sa, ca; //sa is remote socket address
	sa.sin_addr.s_addr = inet_addr(argv[1]); //server's IP
	sa.sin_port = htons(atoi(argv[2])); //server's port
	sa.sin_family = AF_INET;
	printf("UDP client is ok\n");
	while (1) {
		char buf[1000] = { 0 }; //memset(buf,0,1000)
		printf("Client:: ");
		fgets(buf, 1000, stdin);  // take a line of message
		ret = sendto(s, buf, strlen(buf), 0, (SOCKADDR*)&sa, sizeof(sa));
		if (ret == SOCKET_ERROR)quit("sendto");
		memset(buf, 0, 1000);
		ret = recvfrom(s, buf, 1000, 0, NULL, NULL); // in case if we don´t want to know the remote
		
		if (ret == SOCKET_ERROR) quit("recvfrom");
		
		printf("\tServer>> %s\n", buf);
	}
}




