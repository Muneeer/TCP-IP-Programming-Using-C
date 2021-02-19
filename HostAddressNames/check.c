#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include "hosth.h"

void error_handling(char *message);

int main(int argc , char* argv[]) {


	int adr;
	char *oaddr;

  if(argc!=3)
  {
    printf("Usage %s addr\n",argv[0]);
    exit(1);
  }
  
  
  //getting host address of index 0 using domain name 
  adr=get_host_addr(argv[1],0);
  
  printf("IP address of %s : %s\n",argv[1],inet_ntoa(*(struct in_addr*)adr));
  //getting the official name using IP address
  printf("Official Name of IP %s : %s\n",argv[2],get_host_name(argv[2]));
  
  //checking if the entered domain name is official or not
  if((is_official_name(argv[1]))==1)
  	printf("Its Official Name.\n");
  else
  	printf("Its Alias.\n");
  

  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
