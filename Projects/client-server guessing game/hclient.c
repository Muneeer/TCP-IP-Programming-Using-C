#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdbool.h> 
#define BUFF_SIZE 1024

void error_handling(char *message);

int main(int argc , char* argv[]) {

  int serv_sock,str_len,nguess,guess,rnum;
  struct sockaddr_in serv_addr;
  int tguess=0;
  int servcon=1;
  char message[BUFF_SIZE];
  char yn;
  
  bool flag=false;
  bool terminate=false;

while(!terminate) //continue until the client left
{
  serv_sock=socket(PF_INET,SOCK_STREAM,0);

  if(argc!=3)
  {
    printf("Usage %s port\n",argv[1]);
  }

//filling serv_add to zero
  memset(&serv_addr,0,sizeof(serv_addr));

//getting server ip and port
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_addr.sin_port=htons(atoi(argv[2]));


//connect ip and port with the server socket
 if(connect(serv_sock, (struct sockaddr* )&serv_addr,sizeof(serv_addr))==-1)
   error_handling("connect() error");
 
 
 //Starting the game!!
 printf("Welcome!\nThis is Guess Number Game Server.\n(%s:%s)",argv[1],argv[2]);
 
 //reading the total number of coneccted clients. 
 read(serv_sock,&servcon,sizeof(servcon));
 
 //reading the random number from connected server
  read(serv_sock,&rnum,sizeof(rnum));
while(1)
{

  
  printf("\nNumber of Guesses ?>");
  scanf("%d",&nguess);
  tguess+=nguess; //total guesses
  //sending the number of guesses client is gonna make to the server
  write(serv_sock,&nguess,sizeof(nguess));
  int arr[nguess];
  for(int i=0;i<nguess;i++)
  {
  	printf("Answer%d >",i+1);
  	scanf("%d",&arr[i]);
  	if(arr[i]==rnum) //if guessed number is random number
  		flag=true;
  }
  //sending the array of guessed numbers to server
  write(serv_sock,arr,sizeof(arr)); 
  
  //reading the result message from server
  str_len=read(serv_sock, message, BUFF_SIZE-1);
  message[str_len]=0;
  printf("\n[Reply from Server]\n");
  printf("%s\n",message);
  if(flag) // if guess is right
  {
  	printf("You have got it right!!\n");
  	printf("Answer is %d.\n",rnum);
  	printf("Your score is 100/%d=%d\n",tguess,100/tguess);
  	tguess=0;
  	printf("Do you want to play again(y/n) ");
  	scanf(" %c",&yn);
  	if(yn=='y')
  	{
  		
  		printf("\n\n\n");
  		
  		if(servcon==5)//checking if total connections made is equal to listen() backlog arguement.
  		{
  			printf("Sorry the server socket has been closed.\n");
  			//closing the game if client connections reach the value of listen() backlog.
  			terminate=true;
  		}
  		//if client wants to play again close the socket and connect again.
  	break;
  	}
  	else{
  	//if client doenst want to play again close the game.
  		terminate=true;
  		break;
  	}
  	
  	
  }

 }
close(serv_sock);
}



  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
