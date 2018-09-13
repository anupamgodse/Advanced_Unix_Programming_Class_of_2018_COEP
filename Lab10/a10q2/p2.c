#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd1, num=2;
	char *fifofile = "fifofile";
	mkfifo(fifofile, 0666);
	char buf1[4], buf2[4];
	while (num <= 100){
		fd1 = open(fifofile,O_RDONLY);
		read(fd1, buf1, sizeof(buf1));
		printf("P1: %s\t", buf1);
		fflush(NULL);
		close(fd1);

		fd1 = open(fifofile,O_WRONLY);
		snprintf (buf2, sizeof(buf2), "%d",num);
		write(fd1, buf2, sizeof(buf2));
		close(fd1);

		num = num + 2;
	}
	return 0;
}
