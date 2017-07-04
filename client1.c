/** File:	client.c.
 *  Author:	Vishal Chopra.
 *  Date:	03-july-2017.
 *  Brief:	This is for communication between the process using socket IPC mechanism.
 */  

#include "header.h"

#define size_of(type) (char *)(&type + 1) - (char *)&type

int socketCreation();

int main()
{
	socketCreation();
}

int socketCreation()
{
	char buff[64];
	int sockfd, new_sockfd;
	struct sockaddr_in addr, client_addr;
	socklen_t addrlen;
	addr.sin_family = AF_LOCAL;
	addr.sin_port = htons (3333);
	addr.sin_addr.s_addr = INADDR_LOOPBACK;
	sockfd = socket (AF_LOCAL, SOCK_STREAM, 0);
	if (sockfd == -1){
		perror ("socket");
		return -1;
	}
	addrlen = size_of(addr);
	if (connect(sockfd, (struct sockaddr *)&addr, addrlen) == -1){ //function bind sockfd to adress and port number
		perror("bind");
		return -1;
	}
	
	while(1){
		memset(buff, '\0', sizeof(buff));
		printf("Write your message\n");
		fgets(buff, BUFSIZ, stdin);
		write(sockfd, buff, sizeof(buff));
		if(strncmp("exit", buff, sizeof(buff)) == 0)
			break;
	}
		
	close(sockfd);

}
