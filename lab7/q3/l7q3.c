#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	pid_t pid;
	if((pid = fork()) < 0) {
		printf("fork failed");
	}
	else if(pid == 0) {
		execl("mimiccat", "mimiccat", argv[1], argv[2], (char*) NULL);
	}
	else {
		wait(NULL);
	}
	return 0;
}
