#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int fd;
	pid_t pid;
	fd = open("testfile", O_RDWR | O_CREAT, 0777);
	if(fd == -1) {
		printf("open failed\n");
	}
	write(fd, "This is a line added by parent.\n", 32);
	//we will check default status of close on exec flag
	int val = fcntl(fd, F_GETFD);
	if(val) {
		printf("close on exec is set :- %d\n", val);
	}
	else {
		printf("close on exec is not set\n");
	}
	if((pid = fork()) < 0) {
		printf("fork failed\n");
	}
	else if(pid == 0) {
		char buff[20];
		snprintf(buff, 20, "%d", fd);
		printf("%s\n", buff);
		if(execl("progforexec", "progforexec", buff, (char*)NULL) == -1) {
			printf("exec failed\n");
		}
	}
	return 0;
}

