#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd, num = 1;
	char *fifofile = "fifofile";
	mkfifo(fifofile, 0666);
	char buf1[4], buf2[4];
	while (num <= 100){
		fd = open(fifofile, O_WRONLY);
		snprintf (buf2, sizeof(buf2), "%d",num);
		write(fd, buf2, sizeof(buf2));
		close(fd);

		fd = open(fifofile, O_RDONLY);
		read(fd, buf1, sizeof(buf1));
		printf("P2: %s\t", buf1);
		fflush(NULL);
		close(fd);
		num = num + 2;
	}
	return 0;
}
