#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void read_childprocess(int sig);
#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[]) {
	int serv_sock, clnt_sock;
	char message[BUF_SIZE];
	int str_len, i;
	
	pid_t pid;
	
	struct sigaction act;
	act.sa_handler=read_childprocess;
	sigemptyset(act.sa_mask);
	act.sa_flags=0;
	
	
	
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(serv_sock==-1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	if(bind(serv_sock, 
		(struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	
	while(1){
	clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, 
			(struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		if(clnt_sock==-1)
			error_handling("accept() error");
		printf("Connected client \n");
			
		pid=fork();
		
		if(pid==-1)
		{
			
			error_handling("fork() error");
		}else if(pid==0)
		{
			close(serv_sock);
			while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
				write(clnt_sock, message, str_len);
			
			
			
			
			
		}
		else
			
	
		

		close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
	
}

void read_childprocess(int sig)
{
	int status;
	
	pid_t id=waitpid(-1,&status,WNOHANG);
	
	
	
	if(WIFEXIT(status))
	{
		printf("Process Removed %d!!!\n",id);
		printf("Child sends %d!!!\n",WEXITSTATUS(status));
	}
}

