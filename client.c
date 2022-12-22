#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <pthread.h> 
#include <signal.h> 
#include <stdio_ext.h>
#include <arpa/inet.h>
#define MYPORT 2012 
#define MAXDATALEN 256

int sockfd;
int n,x; 
struct sockaddr_in serv_addr; 
char buffer[MAXDATALEN];
char buf[10];

void *quitproc();
void* chat_write(int);
void* chat_read(int);
void *zzz();
int main(int argc, char *argv[])
{
pthread_t thr1,thr2;
if( argc != 2 )
{
printf("help:u need to put server ip\n");
exit(0);
}
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1)
printf ("client socket error\n");
else
printf("socket\t\tcreated\n");
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(MYPORT);
serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
bzero(buf,10);
printf("\nENTER YOUR NAME::");
fgets(buf,10,stdin);

__fpurge(stdin);
buf[strlen(buf)-1]=':';
if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))==-1)
{
printf("client connect error\n");
exit(0);
}
else
printf("%s connected to server\n",buf);
printf("\rYOU JOINED AS- %s",buffer-1);
send(sockfd,buf,strlen(buf),0);
pthread_create(&thr2,NULL,(void *)chat_write,(void *)sockfd);
pthread_create(&thr1,NULL,(void *)chat_read,(void *)sockfd);
pthread_join(thr2,NULL);
pthread_join(thr1,NULL);
return 0;
}

void* chat_read(int sockfd)
{
if (signal(SIGINT,(void *)quitproc)==0)
if(signal(SIGTSTP, (void *)zzz)==0)
while(1)
{

n=recv(sockfd,buffer,MAXDATALEN-1,0);
if(n==0){
printf("\nDUE TO SOME UNEXPECTED REASONS SERVER HAS BEEN
SHUTDOWN\n\n");
exit(0);
}

if(n>0){
printf("\n%s ",buffer);
bzero(buffer,MAXDATALEN);
}
}//while ends

}

void* chat_write(int sockfd)

{
while(1)
{
printf("%s",buf);
fgets(buffer,MAXDATALEN-1,stdin);

if(strlen(buffer)-1>sizeof(buffer))
{
printf("buffer size full \t enter within %lu characters \n",sizeof(buffer));
bzero(buffer,MAXDATALEN);
__fpurge(stdin);
}

n=send(sockfd,buffer,strlen(buffer),0);

if(strncmp(buffer,"quit",4)==0)
exit(0);

bzero(buffer,MAXDATALEN);
}//while ends
}

void *quitproc(){
printf("\rPLEASE TYPE 'quit' TO EXIT\n");

}

void *zzz(){
printf("\rPLEASE TYPE 'quit' TO EXIT\n");

}
