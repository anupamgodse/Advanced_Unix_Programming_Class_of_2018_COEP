#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#define SIZE sizeof(int);
void increment(int semid, int sem_index) {
	struct sembuf sem_op;
	sem_op.sem_flg = 0;
	sem_op.sem_num = sem_index;
	sem_op.sem_op = 1;

	if (semop(semid, &sem_op, 1) < 0) {
		perror("semaphore operation error..!!");
	}
}

void decrement(int semid, int sem_index) {
	struct sembuf sem_op;
	sem_op.sem_flg = 0;
	sem_op.sem_num = sem_index;
	sem_op.sem_op = -1;

	if (semop(semid, &sem_op, 1) < 0) {
		perror("semaphore operation error..!!");
	}
}

int main() {
	int pid = fork();
	if (pid < 0) {
		perror("fork failed");
		return 1;
	}
	key_t sem_key = ftok("a10q3.c", 12);
	key_t shm_key = ftok("a10q3.c", 20);

	if ((sem_key == -1) || (shm_key == -1)) {
		perror("ftok");
		return 1;
	}
	int semid = semget(sem_key, 2, IPC_CREAT | 0600);

	if (semid == -1) {
		perror("semget error:");
		return 1;
	}

	int shmid = shmget(shm_key, 4, IPC_CREAT | 0600);

	if (shmid == -1) {
		perror("shmget error..!!");
		return 1;
	}

	void *mem = shmat(shmid, NULL, 0);
	if (mem == (void *)-1) {
		perror("shmget allocation failed.");
		return 1;
	}

	int i;
	if (pid) {
		/*producer */
		/* Initialize the semaphores */
		int initial_val[2] = {0, 0};
		if (semctl(semid, 0, SETALL, &initial_val[0]) < 0) {
			perror("SETALL failed.");
		}

		increment(semid, 1);
		for (i = 10; i >= 0; i--) {
			decrement(semid, 1);
			printf("producing : %d\n",i);
			*((int *)mem) = i;

			increment(semid, 0);
		}
	}
	else {
		/*consumer */
		/* Wait till parent initializes the semaphores */
		struct semid_ds sem_child;
		do {
			if (semctl(semid, 0, IPC_STAT, &sem_child) < 0) {
				perror("STAT copy error:");
			}
		} while (!sem_child.sem_otime);

		do {
			decrement(semid, 0);
			i = *((int *)mem);
			increment(semid, 1);
			printf("consumed:%d\n", i);
		} while (i);
		
		if (shmctl(shmid, IPC_RMID, NULL) < 0) {
			perror("shmctl(IPC_RMID)");
		}
		if (semctl(semid, 0, IPC_RMID) < 0) {
			perror("semctl(IPC_RMID)");
		}
	}
}
