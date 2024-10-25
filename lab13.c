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
	if (argc < 4) {
		printf("Incorrect number of arguments!\n");
		exit(0);
	}

	int s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1) {
		printf("Socket creation failure.\n");
		exit(0);
	}
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));

	int status = connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (status == 0) {
		int count = send(s, argv[3], strlen(argv[3]), 0);
		if (count == -1) {
			printf("Error sending data!\n");
		} else {
			printf("Sent %d bytes\n", count);
		}
	} else {
		printf("Connection failure!\n");
	}
	close(s);

	return 0;
}
