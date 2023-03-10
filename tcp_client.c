

// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8085

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char cl[1024],sr[1024];
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status
		= connect(client_fd, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	const char deli[] = "`";	
		
	printf("Start Chatting!!\nClient: ");
	scanf("%s",cl);

	while(strcmp(cl,"exit")!=0){
		strcat(cl,deli);
		send(client_fd, cl, strlen(cl), 0);
		getchar();

		valread = read(client_fd, sr, 1024);
		char *token = strtok(sr,deli);
		printf("server: %s\n", token);

		printf("client: ");
		scanf("%s",cl);
	}
	
	
	send(client_fd, cl, strlen(cl), 0);
	printf("Connection Closed\n");
	// closing the connected socket
	close(client_fd);
	return 0;
}

