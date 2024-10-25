#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Socket creation failed\n");
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in addrport;
	addrport.sin_family = AF_INET;
	addrport.sin_port = htons(60111);
	addrport.sin_addr.s_addr = htonl(INADDR_ANY);

	int status = bind(sock, (struct sockaddr *)&addrport, sizeof(addrport));
	if (status == -1) {
		printf("Bind failed!\n");
		close(sock);
		exit(0);
	}

	status = listen(sock, 2);
	if (status == 0) {
		struct sockaddr_in client;
		socklen_t slt = sizeof(client);
		int client_sock = accept(sock, (struct sockaddr *)&client, &slt);
		if (client_sock == -1) {
			printf("Client failure!\n");
		}
		char buf[81];
		int count = recv(client_sock, buf, sizeof(buf) - 1, 0);
		if (count == -1) {
			printf("Receive failed\n");
		} else if (count == 0) {
			printf("Client closed connection\n");
		} else {
			buf[count] = '\0';
			printf("The server received: %s\n", buf);
		}
		close(client_sock);
	} else {
		printf("Error!\n");
	}
	close(sock);

}
