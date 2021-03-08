#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>


#define BUF_SIZE 100
#define MAX_CLNT 256
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
int echo_count=0;
void error_handling(char *message);
void send_msg(char * msg, int len);
void * handle_clnt(void * arg);
fd_set reads,cpy_reads;
pthread_mutex_t mutx;

int main(int argc, char *argv[]) {
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;
	
	pthread_t t_id;
	
	socklen_t adr_sz;
	int fd_max,str_len,fd_num,i;
	char buf[BUF_SIZE];
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	pthread_mutex_init(&mutx,NULL);
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
		
		
		
	FD_ZERO(&reads);
	FD_SET(serv_sock,&reads);
	fd_max=serv_sock;
	
	while(1) {
	cpy_reads=reads;
	timeout.tv_sec=5;
	timeout.tv_usec=5000;

	if((fd_num=select(fd_max+1, &cpy_reads, 0, 0, &timeout))==-1)
		break;
	if(fd_num==0) continue;

	for(i=0; i<fd_max+1; i++) {
		if(FD_ISSET(i, &cpy_reads)) {
			if(i==serv_sock) {	// connection request!
				adr_sz=sizeof(clnt_adr);
				clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
				FD_SET(clnt_sock, &reads);
				if(fd_max<clnt_sock) fd_max=clnt_sock;
				printf("connected client: %d \n", clnt_sock);
				}
			else {	
			
				//pthread_mutex_lock(&mutx);
				//clnt_socks[clnt_cnt++]=clnt_sock;
				//pthread_mutex_unlock(&mutx);
				//echo_count=i-4;
				printf("value of i = %d\n",i);
				pthread_create(&t_id, NULL, handle_clnt, (void*)&i);
				pthread_detach(t_id);
			
				/*					// read message!
				str_len=read(i, buf, BUF_SIZE);
				if(str_len==0) {			// close request!
					FD_CLR(i, &reads);
					close(i);
					echo_count--;
					printf("closed client: %d \n", i);
				}
			else {
				printf("Message is : %s\n",buf);
				pthread_mutex_lock(&mutx);
				clnt_socks[clnt_cnt++]=clnt_sock;
				pthread_mutex_unlock(&mutx);
				echo_count=i-4;
				pthread_create(&t_id, NULL, handle_clnt, (void*)buf);
				pthread_detach(t_id);
				//write(i, buf, str_len);	// echo!
			}*/

			
			
		}
	}
}


/*
	for(i=0; i<5; i++) {
		clnt_sock=accept(serv_sock, 
			(struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		if(clnt_sock==-1)
			error_handling("accept() error");
		else
			printf("Connected client %d \n", i+1);
	
		while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
			write(clnt_sock, message, str_len);

		close(clnt_sock);
	}*/
	}
	close(serv_sock);
	return 0;

}
void * handle_clnt(void * arg){

	int clnt_sock=*((int*)arg);
	printf("value of clnt_sock = %d\n",clnt_sock);
	int str_len=0, i;
	char msg[BUF_SIZE];
	//while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
		//write(clnt_sock, msg,str_len);
	
						// read message!
				str_len=read(clnt_sock, msg, BUF_SIZE);
				if(str_len==0) {			// close request!
					FD_CLR(i, &reads);
					close(i);
					echo_count--;
					printf("closed client: %d \n", i);
				}
			else {
				
				write(clnt_sock, msg, str_len);	// echo!
			}

	//char *msg=(char*)arg;
	//printf("Hey in the handle control!! %s\n",msg);
	//int str_len=0, i;
	//read(i, buf, BUF_SIZE);
	//char msg[BUF_SIZE];
	
	/*while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0)
		send_msg(msg, str_len);
	
	printf("Message is : %s\n",msg);
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++) {  
		if(clnt_sock==clnt_socks[i]) {
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);*/
	return NULL;
}

void send_msg(char * msg, int len) {
	//int i;
	//pthread_mutex_lock(&mutx);
	//for(i=0; i<clnt_cnt; i++)
		//write(clnt_socks[i], msg, len);
	//pthread_mutex_unlock(&mutx);
}
void error_handling(char *message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
	
}

