#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int p1[2],p2[2],p3[2],p4[2];
    int val = 0;
    int t = 0;
    int m = 0;
    int l = 0;
	pid_t pid_c1, pid_c2;
    
    pipe(p1);
    pipe(p2);
    pipe(p3);
    pipe(p4);

    if ((pid_c1 = fork()) != 0){
        close(p1[0]);

        val = 100;
        write(p1[1], &val, sizeof(val));
        printf("Parent(%d) send value: %d\n", getpid(), val);

        close(p1[1]);
        
        close(p2[1]);
        read(p2[0], &val, sizeof(val));
        printf("Parent(%d) received value: %d\n", getpid(), val);
        close(p2[0]);
        
        if(pid_c2 = fork() != 0){
        	close(p4[1]);
        	read(p4[0], &m, sizeof(m));
        	printf("Parent(%d) received value: %d\n", getpid(), m);
        	close(p4[0]);
        }
        else{
        	m = 90;
        	close(p4[0]);
        	write(p4[1],&m,sizeof(t));
        	printf("Child(%d) send value: %d\n", getpid(), m);
       		close(p4[1]);
       		
       		close(p3[1]);
        	read(p3[0], &l, sizeof(l));
        	printf("Child(%d) received value: %d\n", getpid(), l);
        	close(p3[0]);
       	}
       	
    }
    else{  
        close(p1[1]);
        read(p1[0], &val, sizeof(val));
        printf("Child(%d) received value: %d\n", getpid(), val);
        close(p1[0]);
        
        t = 50;
        close(p2[0]);
        write(p2[1],&t,sizeof(t));
        printf("Child(%d) send value: %d\n", getpid(), t);
        close(p2[1]);
        
        close(p3[0]);
        l = 45;
        write(p3[1], &l, sizeof(l));
        printf("Child(%d) send value: %d\n", getpid(), l);
        close(p3[1]);
    }
    return 0;
}
