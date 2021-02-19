#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>



void error_handling(char *message);

int main(int argc , char* argv[]) {
  	struct hostent *host;
	struct in_addr addrr;
	
	  /*if(argc!=2)
  {
    printf("Usage %s <IP>\n",argv[0]);
    exit(1);
  }*/
	//printf("%s\n",addr);
	inet_aton("74.125.19.106",&addrr);
	host=gethostbyaddr(&addrr,sizeof(addrr), AF_INET);
  
  	if(!host)
  	{
  		error_handling("gethost.... error");
 	 }
  
  	printf("Official name :  %s\n",host->h_name);
  
  

  return 0;
}
void error_handling(char *message){
  fputs(message,stderr);
  fputs("\n",stderr);
  exit(1);
}
