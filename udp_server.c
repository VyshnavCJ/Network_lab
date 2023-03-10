// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;
	const char deli[]="`";
	len = sizeof(cliaddr); //len is value/result
	char cl[1024],sr[1024];
	recvfrom(sockfd, (char *)cl, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);		
	char *token = strtok(cl,deli);
	printf("Client: %s\n",token);
	while(strcmp(token,"exit")!=0){
		printf("Server: ");
		scanf("%s",sr);
		strcat(sr,deli);
		sendto(sockfd, (char *)sr, strlen(sr),
		MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
			len);
		getchar();
		recvfrom(sockfd, (char *)cl, MAXLINE,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
		char *token = strtok(cl,deli);
		printf("Client: %s\n",token);

	}
	printf("Connection Closed \n");
		
	return 0;
}

