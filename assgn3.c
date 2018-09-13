#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
int main() {
	int fd;
	fd = open("f1", O_WRONLY | O_CREAT, 777);
	if(fd == -1) {
		perror("error openeing file");
		return 0;
	}
	
	if(write(fd, "abcde", 5) != 5) {
		printf("hi\n");
		perror("error writing to file");
		return 0;
	}
	close(fd);
	
	fd = open("f1", O_WRONLY | O_APPEND);
	lseek(fd, 0, SEEK_SET);
	if(write(fd, "12345", 5) != 5) {
		printf("hi\n");
		perror("error writing to file");
		return 0;
	}
	close(fd);
	return 0;
}
