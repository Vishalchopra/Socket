/** File:	server.c.
 *  Author:	Vishal Chopra.
 *  Date:	02-july-2017.
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
	int sockfd;
	struct sockaddr_in addr;
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
	if (bind(sockfd, (struct sockaddr *)&addr, addrlen) == -1){
		perror("bind");
		goto err;
	}
	
		
err:
	close(sockfd);

}
