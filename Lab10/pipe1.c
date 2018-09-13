#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
static int pfd1[2], pfd2[2];
void TELL_WAIT(void) {
	if(pipe(pfd1) < 0 || pipe(pfd2) < 0)
		perror("pipe error");
}
void TELL_PARENT(void){
	if(write(pdf2[1],'c',1) != 1)
		perror("Error while writing..!!");
}
void TELL_CHILD(void){
	if(write(pdf2[2],'p',1) != 1)
		perror("Error while writing...");
}
void WAIT_PARENT(void){
	char c;
	if (read(pfd1[0], &c, 1) != 1)
		perror("read error");
	if (c != 'p')
		perror("WAIT_PARENT: incorrect data");
}
void TELL_CHILD(pid_t pid) {
	if (write(pfd1[1], 'p', 1) != 1)
		perror("write error");
}
void WAIT_CHILD(void) {
	char c;
	if(read(pfd2[0], &c, 1) != 1)
		perror("read error");
	if (c != 'c')
		perror("WAIT_CHILD: incorrect data");
}
int main(){
	int n;
	int fd[2];
	pid_t pid;
	char buff[128];
	if(pipe(fd) < 0){
		printf("Error in allocating pipe.");
	}
	if((pid = fork()) < 0){
		printf("fork error");
	}
	else if(pid > 0){
		close(fd[0]);
		write(fd[1],"Hello from parent..!!!",23);
	}
	else{
		close(fd[1]);
		n = read(fd[0],buff,128);
		write(1,buff,n);
	}
	return 0;
}
