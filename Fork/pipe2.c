#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#define BUF_SIZE 40

int main(int argc, char *argv[]) {
	int fds1[2],fds2[2];
	char str[]="Who are you?";
	char str2[]="I am fine thanks for your reply.";
	char buf[BUF_SIZE];
	pid_t pid;
	
	pipe(fds1),pipe(fds2);
	pid=fork();
	if(pid==0) {
		write(fds1[1], str, sizeof(str));
		read(fds2[0], buf, BUF_SIZE);
		puts(buf);
	}
	else {
		read(fds1[0], buf, BUF_SIZE);
		puts(buf);
		//sleep(2);
		write(fds2[1], str2, sizeof(str2));
		//puts(buf);
		//sleep(3);

	}
	return 0;
}

