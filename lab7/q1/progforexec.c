#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int fd = atoi(argv[1]);
	if(write(fd, "This is line written by program executed in child using exec().\n", 
			strlen("This is line written by program executed in child using exec().\n")) < 0) {
		printf("Demonstration failed\n");
	}
	else {
		printf("The child “exec” call inherits the file descriptors of parent if Close_on_exec is not set : Demonstation successfull\n");
		exit(0);
	}
	return 0;
}
