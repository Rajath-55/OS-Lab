#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
    int fd[2];
    int fd2[2];

    char message[] = "Is this the real life!";
    

    if(pipe(fd) == -1){
        fprintf(stderr, "Failed");
        return 1;
    }
    if(pipe(fd2) == -1){
        fprintf(stderr, "Failed");
        return 1;
    }
    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "Failed");
        return 1;
    }
    if(pid > 0){
        close(fd[0]);
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);

        wait(NULL);
        close(fd2[1]);
        char changed[100];
        read(fd2[0], changed, sizeof(changed) + 1);
        printf("Converted : %s\n", changed);
        close(fd2[0]);
    }else{
        close(fd[1]);
        
        char inp[100];
        read(fd[0], inp, sizeof(inp) + 1);
        close(fd[0]);
        for(int i = 0; i < strlen(inp); i++){
            if(tolower(inp[i]) == inp[i]){
                inp[i] = toupper(inp[i]); 
            }else{
                inp[i] = tolower(inp[i]);
            }
        }
        close(fd2[0]);
        write(fd2[1], inp, strlen(inp) + 1);
        close(fd2[1]);
        exit(0);
    }


    return 0;
}