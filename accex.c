#include<stdio.h> 
#include<stdlib.h>
#include<sys/acct.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
int main(void)
{
pid_t pid;
if ((pid = fork()) < 0)
printf("fork error");
else if (pid != 0) { /* parent */
sleep(2); exit(2); /* terminate with exit status 2 */ } /* first child */
if ((pid = fork()) < 0) printf("fork error"); /* first child */
else if (pid != 0) {/* first child */
sleep(4); abort(); /* terminate with core dump */ }
if ((pid = fork()) < 0) printf("fork error"); /* second child */
else if (pid != 0) {/* second child */
execl("/bin/ls", "ls", NULL);
exit(7); /* shouldn't get here */ }
if ((pid = fork()) < 0) printf("fork error"); /* third child */
else if (pid != 0) {/* third child */
sleep(8); exit(0); /* normal exit */
sleep(6); } /* fourth child */
kill(getpid(), SIGKILL); /* terminate w/signal, no core dump */
exit(6); /* shouldn't get here */
}
