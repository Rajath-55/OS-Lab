#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int x;
    int count = 0;
    while(argv[++count]);
    if(count < 2)
    {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }

    char *str = *(argv + 1);
    sscanf(str, "%d", &x);
    // printf("%d\n", x);
    if(x < 0){
        printf("Invalid input\n");
        return 1;
    }
    pid_t pid = fork();

    if(pid < 0){
	    fprintf(stderr, "Error in creating Child\n");
    }
    else if(pid == 0){
        int *shm_ptr;
        int shmid;
        key_t key;
        key = 5678;
        shmid = shmget(key, 1024, IPC_CREAT | 0666);
        shm_ptr = (int*) shmat(shmid, (void *)0, 0);
        int *ptr = shm_ptr;
        int i = 0;
        
        while(x != 1){
            if(x%2 == 0){
                *(ptr + i) = x/2;
                x/=2;
                i++;
            }else{
                *(ptr + i) = x*3 + 1;
                x = 3*x + 1;
                i++;
            }
        }
        *(ptr + i) = 1;
        shmdt(shm_ptr);
        exit(0);
    }
    else{
        int *shm_ptr;
        int shmid;
        key_t key;
        key = 5678;
        wait(NULL);
        shmid = shmget(key, 1024, 0);
        shm_ptr = (int *) shmat(shmid, (void*) 0, 0);
        printf("Received from shared memory through child : \n");
        printf("%d ", x);
        while(*shm_ptr != 1){
            printf("%d ", *shm_ptr);
            shm_ptr++;
        }
        printf("%d\n",1);
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}