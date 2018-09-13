#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	/*if(setuid(1000) == -1) {
		printf("setuid failed\n");
	}*/	
	pid_t pid;
	
	if((pid = fork()) < 0) {
		printf("fork failed\n");
	}
	else if(pid == 0) {
		execl("/bin/cat", "cat", argv[1], (char*)0);
	}
	else {
		wait(NULL);
	}
	return 0;
}
