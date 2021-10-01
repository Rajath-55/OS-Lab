#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100
  
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;
  
int main()
{
    key_t key = 5678;
    int msgid;
  
    
    msgid = msgget(key, 0666 | IPC_CREAT); //create
    message.msg_type = 1;
  
    fgets(message.msg_text,MAX,stdin); 
    msgsnd(msgid, &message, sizeof(message) + 1, 0); //send
  
  
    return 0;
}