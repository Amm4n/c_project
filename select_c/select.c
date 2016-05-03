#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock;
	unsigned int len;
	struct sockaddr_in server;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if ( sock < 0 )
		error("Socket : ");

	server.sin_family = AF_INET;
	server.sin_port = htons(2808);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
		
	len = sizeof(struct sockaddr_in);
	
	if( (bind(sock, (struct sockaddr *)&server, len)) < 0 )
		error("bind");
	if( (listen(sock, 5)) < 0 )
		error("listen");

	int optval, optval1, get;
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &optval, &len);
	printf("Buffer Size For Output : %d\n",  optval);
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &optval, &len);
	printf("Buffer Size For Input : %d\n", optval);
	optval = 35834;	
	optval1 = 468973;
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &optval, sizeof(optval));
	printf("Buffer SIze For Output Set to %d!\n", optval);
	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &optval1, sizeof(optval1));
	printf("Buffer Size For Input Set to %d!\n", optval1);
	getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &optval, &len);
	printf("New Buffer Size For Output : %d\n", optval);
	getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &optval1, &len);
	printf("New Buffer Size For Input : %d\n", optval1);
}