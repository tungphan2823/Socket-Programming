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
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == SOCKET_ERROR) quit("Create SOCKET");
	printf("Socket is Ready\n");
	SOCKADDR_IN sa, ca; //local socket address
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = htons(atoi(argv[1])); //htons changes endianess
	sa.sin_family = AF_INET;
	ret = bind(s, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)quit("binding");
	printf("Binding is ok\n");
	ret = listen(s, 5);
	if (ret == SOCKET_ERROR) quit("listen");
	printf("Server is listening on port %s\n", argv[1]);
	while (1) {
		int clen = sizeof(ca);
		SOCKET cs = accept(s,(SOCKADDR*)&ca, &clen);
		if (cs == INVALID_SOCKET)quit("accept");
		printf("Client %s:%d is connected\n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));
		//From this moment we should make multi-process programming
		while (1) { // communicating with the client
			char buf[1000] = { 0 };
			ret = recv(cs, buf, 1000, 0);
			if (ret == SOCKET_ERROR)quit("recv");
			printf("\tClient >> %s\n", buf);
			if (buf[0] == '#')break;
			printf("Return :: ");
			memset(buf, 0, 1000);
			fgets(buf, 1000, stdin);
			ret = send(cs, buf, strlen(buf), 0);
		}
		closesocket(cs); //destroy the client socket
		break;
	}
}




