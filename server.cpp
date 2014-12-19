#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<iostream>
using std::cout;

int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cout << "Create socket failed.\n";
		return 0;
	}
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(6666);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		std::cout << "Bind socket failed.\n";
		return 0;
	}
	if (listen(sockfd, 8) < 0) {
		std::cout << "Listen socket failed.\n";
		return 0;
	}
	std::cout << "======== Listening to port 6666 ============\n";
	char buffer[4096];
	while (true) {
		int connfd;
		if ((connfd = accept(sockfd, (struct sockaddr *)NULL, 0)) < 0) {
			std::cout << "Connect failed.\n";
			continue;
		}
		int len = recv(connfd, buffer, 4096, 0);
		buffer[len] = 0;
		buffer[len + 1] = '\n';
		std::cout << buffer << '\n';
		close(connfd);
	}
	close(sockfd);
	return 0;
}
