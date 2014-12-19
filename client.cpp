#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<iostream>
using std::cout;

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "usage: ./client <ip_address>\n";
		return 0;
	}
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		std::cout << "Create socket failed.\n";
		return 0;
	}
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(6666);
	if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
		std::cout << "inet_pton failed.\n";
		return 0;
	}
	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		std::cout << "Connect failed.\n";
		return 0;
	}
	char msg[] = "Hello World";
	if (send(sockfd, msg, strlen(msg), 0) < 0) {
		std::cout << "Send message failed.\n";
		return 0;
	}
	std::cout << "Finished\n";
	close(sockfd);
	return 0;
}
