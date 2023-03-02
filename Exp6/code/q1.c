#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#define READERS_NUM 2
#define MAX_COUNT 5

int shmid;

typedef struct {
    int count, read_count;
    pthread_mutex_t mutex;
    pthread_mutex_t rw_mutex;
} ShMemory;

void reader() {
    ShMemory* shmem;
    if ((shmem = (ShMemory *)shmat(shmid, NULL, 0)) == (ShMemory *) -1) {
        printf("ERROR: shmat");
        exit(1);
    }
    int pid = getpid();

    int finish = 0;
    while (finish == 0) {
        pthread_mutex_lock(&(shmem->mutex));
        (shmem->read_count)++;
        if (shmem->read_count == 1) {
            pthread_mutex_lock(&(shmem->rw_mutex));
        }
        pthread_mutex_unlock(&(shmem->mutex));

        printf("*READER => pid: %d count: %d\n", pid, shmem->count);
        if (shmem->count >= MAX_COUNT) {
            finish = 1;
        }

        pthread_mutex_lock(&(shmem->mutex));
        (shmem->read_count)--;
        if (shmem->read_count == 0) {
            pthread_mutex_unlock(&(shmem->rw_mutex));
        }
        pthread_mutex_unlock(&(shmem->mutex));
        sleep(0.1);
    }

    if (shmdt(shmem) == -1) {
        printf("ERROR: shmdt");
        exit(1);
    }
}

void writer() {
    ShMemory* shmem;
    if ((shmem = (ShMemory *)shmat(shmid, NULL, 0)) == (ShMemory *) -1) {
        printf("ERROR: shmdt");
        exit(1);
    }
    int pid = getpid();

    int finish = 0;
    while (finish == 0) {
        pthread_mutex_lock(&(shmem->rw_mutex));

        shmem->count++;
        printf("*Writer => PID: %d count: %d\n", pid, shmem->count);
        if (shmem->count >= MAX_COUNT) {
            finish = 1;
        }

        pthread_mutex_unlock(&(shmem->rw_mutex));
        sleep(0.05);
    }

    if (shmdt(shmem) == -1) {
        printf("ERROR: shmdt");
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    if ((shmid = shmget(IPC_PRIVATE, sizeof(ShMemory), IPC_CREAT | 0666)) < 0) {
        printf("ERROR: shmget");
        exit(-1);
    }

    ShMemory* shm_ptr;
    if ((shm_ptr = (ShMemory *)shmat(shmid, NULL, 0)) == (ShMemory *) -1) {
        printf("ERROR: shmat");
        exit(1);
    }
    ShMemory->count=0;
    ShMemory->read_count=0;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&(shm_ptr->mutex), &attr);
    pthread_mutex_init(&(shm_ptr->rw_mutex), &attr);

    if (shmdt(shm_ptr) == -1) {
        printf("ERROR: shmdt");
        exit(1);
    }

    int parent_id = getpid();

    // create writer process
    int pid = fork();
    if (pid == 0) {
        writer();
        return 0;
    }

    // create reader processes
    for (int i = 0; i < READERS_NUM; i++)
    {
        if (getpid() == parent_id)
            pid = fork();
        else
            break;
    }

    if (pid == 0) { // reader processes
        reader();
        return 0;
    }


    if (getpid() == parent_id) // parent process
    {
        // wait for writer and readers
        for (int i = 0; i < READERS_NUM + 1; i++)
        {
            wait(NULL);
        }
    }

    if(-1 == (shmctl(shmid, IPC_RMID, NULL)))
    {   
        printf("ERROR: shmctl");
        exit(1);
    }
    return 0;
}
