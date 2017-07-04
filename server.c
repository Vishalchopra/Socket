/** File:	server.c.
 *  Author:	Vishal Chopra.
 *  Date:	02-july-2017.
 *  Brief:	This is for communication between the process using socket IPC mechanism.
 */  

#include "header.h"

/***********************Macro Defination***********************/
#define MAXSIZE 5
#define size_of(type) (char *)(&type + 1) - (char *)&type

/***************************Function Prototype***************************/
int socketCreation ();
int funcCreateThread (int);
void *threadCommunicate(void *);

/******************Global Variable*********************************/
pthread_t pthread[MAXSIZE];
int index_thread;

int main ()
{
	socketCreation();
}

/*********************Function to create Socket****************/
int socketCreation ()
{
	int sockfd, new_sockfd;
	struct sockaddr_in addr, client_addr;
	socklen_t addrlen;
	addr.sin_family = AF_LOCAL;
	addr.sin_port = htons (4334);
	addr.sin_addr.s_addr = INADDR_LOOPBACK;
	sockfd = socket (AF_LOCAL, SOCK_STREAM, 0);
	if (sockfd == -1){
		perror ("socket");
		return -1;
	}
	addrlen = size_of(addr);
	if (bind(sockfd, (struct sockaddr *)&addr, addrlen) == -1){ //function bind sockfd to adress and port number
		perror("bind");
		return -1;
	}
	
	listen(sockfd, MAXSIZE);	//maximum length of queue
	while(1){
		new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
		if(new_sockfd < 0){
			perror("accept");
		}
		funcCreateThread(new_sockfd);
	}
		

}
/***************************Function to create thread**************************/
int funcCreateThread (int fd)
{
	pthread_attr_t attr;
	if(pthread_attr_init(&attr)){	// to initialize attribute
		perror("pthread_attr_init");
		exit(EXIT_FAILURE);
	}	

	if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)){
		perror("pthread_attr_setdetachedstate");
		exit(EXIT_FAILURE);
	}

	pthread_create(&pthread[index_thread], &attr, &threadCommunicate, (void *)&fd);
	index_thread++;
}

void *threadCommunicate(void *fd)
{
	char buff[64];
	int new_fd = *(int *)fd;
	while(1){
		memset(buff, '\0', sizeof(buff));
		read(new_fd, buff, sizeof(buff));
		if(strncmp(buff, "exit", 4) == 0)
			break;
		printf("message from fd: %d is %s\n", new_fd, buff);
	
	}
	close(new_fd);
}
