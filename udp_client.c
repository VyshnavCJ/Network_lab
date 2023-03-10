// Client side implementation of UDP client-server model
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
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
		
	int n, len;

	const char deli[]="`";

	printf("Start Chatting!!\nClient: ");
	char cl[1024],sr[1024];
	scanf("%s",cl);

	while(strcmp(cl,"exit")!=0){

		int len;
		strcat(cl,deli);
		sendto(sockfd, (char *)cl, strlen(cl),
                MSG_CONFIRM, (const struct sockaddr *) &servaddr,
                        sizeof(servaddr));
        	getchar();

        	recvfrom(sockfd, (char *)sr, MAXLINE,
                                MSG_WAITALL, (struct sockaddr *) &servaddr,
                                &len);
    		
		char *token = strtok(sr,deli);
        	printf("Server: %s\n", token);
		printf("Client: ");
		scanf("%s",cl);
	}
		
	strcat(cl,deli);
	sendto(sockfd, (char *)cl, strlen(cl),
		MSG_CONFIRM, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Connection Closed\n");
	
	close(sockfd);
	return 0;
}

