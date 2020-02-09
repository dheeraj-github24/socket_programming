#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define SERV_TCP_PORT 8088
#define SERV_HOST_ADDR "127.0.0.1"
#define MAXLINE 512

main()
{
  int sockfd,newsockfd,clilen,childpid;
  struct sockaddr_in cli_addr,serv_addr;
  char buf[256];


  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))<0)
//printf("sockfd = %d\n", sockfd);
    printf("Server cannot open stream socket\n");


  bzero((char *) &serv_addr,sizeof(serv_addr));


  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_TCP_PORT);
  serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);

  if(bind(sockfd, &serv_addr, sizeof(serv_addr))<0)
     printf("Server cannot bind local address\n");

  listen(sockfd,1);

  for(;;)
   {
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd,(struct sockaddr *) & cli_addr, &clilen);

if(newsockfd<0)
 printf("Server accept error\n");
if((childpid = fork())<0)
 printf("server fork error\n");
else
if(childpid == 0)
 {
printf("pid is %d\n", childpid);
close(sockfd);
 }

read(newsockfd,buf,30);
buf[30] = 0;

printf("Server reads: ' %s '\n",buf);

write(newsockfd, "Server Received",20);

exit(0);
    }

   close(newsockfd);
  }

