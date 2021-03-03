#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>

#define BUFF_SIZE 1024
void error_handling(char *message);

int main(int argc , char* argv[]) {

//Variables to use
  int serv_sock,clnt_sock,i,str_len,rnum,nguess,servcon;
  char message[BUFF_SIZE];
  int DOWN=0;int UP=0;int HIT=0;
  struct sockaddr_in serv_addr,clnt_addr;
  socklen_t clnt_addr_sz;

 // setting a different seed of random number
  srand(time(NULL));
  
  if(argc!=2) //checking the number of arguements
  {
    printf("Usage %s port\n",argv[0]);
  }
  
  //creating server socket
  serv_sock=socket(PF_INET,SOCK_STREAM,0);

  memset(&serv_addr,0,sizeof(serv_addr));

//getting server ip and port
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_addr.sin_port=htons(atoi(argv[1]));

//bind server socket to server ip and port
  if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))==-1)
  {
    error_handling("bind() error");
  }

//listening for connections on server socket
  if(listen(serv_sock,5)==-1)
  {
    error_handling("listen() error");
  }

  clnt_addr_sz=sizeof(clnt_addr);

for(i=0;i<5;i++) //loop till the listen() backlog value.
{
  
  printf("Waiting for Client...\n");
  //making connections on server socket
  clnt_sock=accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_sz);
  if(clnt_sock==-1){
    error_handling("accept() error");
  }
  printf("Client %d is connected!!\n",i+1);
  servcon=i+1; //number of connections made
  
  //sending the total number of coneccted clients to server. 
  write(clnt_sock,&servcon,sizeof(servcon));
  rnum = rand() % 100 + 1; //creating a random number between 1-100
  printf("Randomly generated number is %d.\n",rnum);
  
  //sending random number to client
   write(clnt_sock,&rnum,sizeof(rnum));

//reading the number of guesses from client
 read(clnt_sock,&nguess,sizeof(nguess));
 int arr[nguess];
 //getting the guessed values from server
    while((str_len=read(clnt_sock,&arr,BUFF_SIZE))!=0)
 {
  printf("\n\nClient%d’s answers: ",i+1);
  for(int j=0;j<nguess;j++)
  {
  	printf("%d ",arr[j]);
  	if(arr[j]>rnum)
  		UP++;
  	else if(arr[j]<rnum)
  		DOWN++;
  	else
  		HIT++;
  }
  
  printf("\n");
  
  //concatenating message with the result
  sprintf(message, "UP %d, DOWN %d, HIT %d",UP,DOWN,HIT);
  printf("Reply : %s\n\n\n",message);

  //writing message to the client
  write(clnt_sock,message,strlen(message));
  
  //initial it to zero
  UP=0;DOWN=0;HIT=0;
  message[0]='\0'; //empty the message
 
 //reading the number of guesses from client
 read(clnt_sock,&nguess,sizeof(nguess));
 int arr[nguess];
  
}
printf("Client %d left..\n",i+1);

  close(clnt_sock);
}
  
  
  close(serv_sock);
  
  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
