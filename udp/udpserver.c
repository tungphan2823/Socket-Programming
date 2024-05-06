#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include  <stdio.h>
#include <WinSock2.h>

void quit(const char* msg) {
	printf("Error: %s\n", msg);
	exit(1);
}
int main(int argc, char** argv) {
	if (argc != 2) quit("Command argument problem");
	WSADATA w;
	int ret = WSAStartup(MAKEWORD(2, 2), &w);
	if (ret == 1)quit("Winsock API");
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == SOCKET_ERROR) quit("Create SOCKET");
	printf("Socket is Ready\n");
	SOCKADDR_IN sa, ca; //local socket address
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = htons(atoi(argv[1])); //htons changes endianess
	sa.sin_family = AF_INET;
	ret = bind(s, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)quit("binding");
	printf("Binding is ok\n");
	while (1) {
		char buf[1000] = { 0 }; //memset(buf,0,1000)
		int rlen = sizeof(ca);
		ret = recvfrom(s, buf, 1000, 0, (SOCKADDR*)&ca, &rlen); // in case if we don´t want to know the remote
		if (ret == SOCKET_ERROR) quit("recvfrom");
		printf("Client (%s:%d): %s\n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port), buf);
		printf("\tServer Reply: ");
		memset(buf, 0, 1000); //Clear buffer for sending
		fgets(buf, 1000, stdin);  // take a line of message
		ret = sendto(s, buf, strlen(buf), 0,(SOCKADDR*) &ca, sizeof(ca));
	}
}




