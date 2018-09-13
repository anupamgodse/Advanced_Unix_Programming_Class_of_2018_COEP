// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
int main(){
    int fd;
	int i = 0;
	int j = 0; 
    // FIFO file path
    char * myfifo = "/home/vijesh1996/Desktop/myfifo";
 
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
 
    char arr1[80], arr2[80];
    while (i < 100){
    	i = j * 2;
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
 
        // Take an input arr2ing from user.
        // 80 is maximum length
        //fgets(arr2, 80, stdin);
 
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, &i, sizeof(i));
        close(fd);
 
        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);
 
        // Read from FIFO
        read(fd, arr1, sizeof(arr1));
 
        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
        j++;
    }
    return 0;
}
