#define _GNU_SOURCE             
#include<sched.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
typedef struct params {							/*parameter structure*/
        pthread_mutex_t mutex;                             
        pthread_cond_t done;							   
        int cpu_id;											
}params;
void* hello(void *arg){
	pthread_mutex_lock(&(*(params*)(arg)).mutex);	/*mutext lock on arguements*/			
    int cpu = (*(params*)(arg)).cpu_id;								
	pthread_t thread = pthread_self();				/*get thread self_id*/
	cpu_set_t cpuset;			
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);							
	//int k = 2000000000;											
	int s = pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
	if (s != 0)
		printf("Error for CPU %d\n", cpu);
	if(CPU_ISSET(cpu,&cpuset) != 0){
		printf("CPU %d is assigned to Thread %lu\n",cpu,thread);
	}
	//while(k){									 // dummy loop to observe o/p 
	//	k--;									// using system monitor
	//}
	pthread_mutex_unlock(&(*(params*)(arg)).mutex);
    pthread_cond_signal(&(*(params*)(arg)).done);
    pthread_exit(NULL);
}
int main(){
	params pars;
    pthread_mutex_init(&pars.mutex , NULL);
    pthread_cond_init(&pars.done, NULL);    
    pthread_mutex_lock (&pars.mutex);
    int j;
	long int n_cpu =  sysconf(_SC_NPROCESSORS_ONLN);
	printf("There are %ld CPUs.\n",n_cpu);
	pthread_t threads[n_cpu];
	for (j = 0; j < n_cpu; j++){
		pars.cpu_id = j;
		pthread_create(&threads[j], NULL, hello, &pars);
		pthread_cond_wait (&pars.done, &pars.mutex);
	}
	for(j = 0; j < n_cpu ; j++) {
            pthread_join(threads[j], NULL);
    }
    pthread_mutex_destroy (&pars.mutex);
    pthread_cond_destroy (&pars.done);
    return 0;	
}
