#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define SERV_TCP_PORT 8088
#define SERV_HOST_ADDR "127.0.0.1"
#define MAXLINE 512


int main()
{
	int sd;
	// comment
	struct sockaddr_in serv_addr;
	char buf[256];
	//open a TCP socket (a internet stream socket).
	bzero((char *) &serv_addr,sizeof(serv_addr));
	//fill zero
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_TCP_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);

	if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
		printf("Server can't open stream socket\n");
	if(connect(sd,(struct sockaddr *)& serv_addr,sizeof(serv_addr))<0)
		printf("Client : can't connect to server\n");
		printf("enter the message to send to the server\n");
		scanf("%[^\n]s",buf);
		int length;
		length=strlen(buf);
		if(length>10)
		{
			printf("this message is bigger than expected\n");
			exit(0);
		}
		else
		{
		write(sd,buf,strlen(buf));
		
		read(sd,buf,30);
		buf[30]=0;
		printf("CLIENT RECIEVES: '%s'\n",buf);
		}
}

