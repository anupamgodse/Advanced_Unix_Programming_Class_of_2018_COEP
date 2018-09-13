#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int fd, count = 0;
	pid_t pid;
	char *arg[128];
	fd = open("testfile", O_RDONLY);
	if(fd == -1) {
		printf("Open failed\n");
	}
	char buff[128];
	read(fd, buff, 128);
	//printf("%s\n", buff);
	char *token = strtok(buff, " \n");
	while(token) {
		arg[count++] = token;
		//printf("%s\n", token);
		token = strtok(NULL, " \n");
	}
	arg[count] = NULL;
	if((pid = fork()) < 0) {
		printf("fork failed\n");
	}	
	else if(pid == 0) {
		execvp(arg[0], arg);
	}
	else {
		wait(NULL);
	}
	return 0;
}
