#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct params {
        pthread_mutex_t mutex;                         // mutex lock for sync
        pthread_cond_t done;						  // done conditional variable
        int id;										 //	 id variable which we want to print
}params;
void* printId(void* arg){
    int id;
    pthread_mutex_lock(&(*(params*)(arg)).mutex);	/* Lock.  */
    id = (*(params*)(arg)).id;
    printf("Hello from Thread %d\n", id);
    pthread_mutex_unlock(&(*(params*)(arg)).mutex);
    pthread_cond_signal(&(*(params*)(arg)).done);

}
int main() {
    pthread_t threads[5];
    params pars;
    pthread_mutex_init (&pars.mutex , NULL);
    pthread_cond_init (&pars.done, NULL);

    pthread_mutex_lock (&pars.mutex);        /* Obtain a lock on the parameter.  */
    int i;
    for(i = 0; i < 5; i++) {  
            pars.id = i;
            pthread_create(&threads[i], NULL, printId, &pars);
            pthread_cond_wait (&pars.done, &pars.mutex); /* Give up the lock, wait till thread is 'done',
            											 then reacquire the lock.  */
    }
    for(i = 0; i < 5; i++) {
            pthread_join(threads[i], NULL);
    }
    /* Destroy all synchronization primitives.  */    
    pthread_mutex_destroy (&pars.mutex);
    pthread_cond_destroy (&pars.done);
    return 0;
}


