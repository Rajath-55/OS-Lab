// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
  
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;
  
int main()
{
    key_t key = 5678;
    int msgid;
    
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    msgrcv(msgid, &message, sizeof(message) + 1, 1, 0); //receive
  
    printf("Data Received is : %s \n", 
                    message.msg_text); 
  
    msgctl(msgid, IPC_RMID, NULL); //destroy
  
    return 0;
}