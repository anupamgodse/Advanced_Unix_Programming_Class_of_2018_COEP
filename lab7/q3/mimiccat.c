#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int fd1, fd2;
	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1) {
		printf("open failed\n");
	}
	fd2 = open(argv[2], O_WRONLY | O_CREAT, 0777);
	if(fd2 == -1) {
		printf("open failed\n");
	}
	char buff[128];
	int n;
	while(n = read(fd1, buff, 128)) {
		write(fd2, buff, n);
	}
	return 0;
}
