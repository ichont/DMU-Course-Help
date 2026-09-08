#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main(){
int msgid; int status;
char str1[ ]={"test message:hello!"};
char str2[ ]={"test message:goodbye!"};
char str3[ ]={"The third message!"};
struct msgbuf{
long msgtype;
char msgtext[1024];
}sndmsg,rcvmsg;
if((msgid = msgget(IPC_PRIVATE,0666)) == -1){
printf("msgget error!\n");
exit(254);
}
sndmsg.msgtype = 111;
sprintf(sndmsg.msgtext,str1);
if(msgsnd(msgid,&sndmsg,sizeof(str1)+1,0) == -1){
printf("msgsnd error!\n");
exit(254);
}
sndmsg.msgtype = 222;
sprintf(sndmsg.msgtext,str2);
if(msgsnd(msgid,&sndmsg,sizeof(str2)+1,0) == -1){
printf("msgsnd error!\n");
exit(254);
}
sndmsg.msgtype = 333;
sprintf(sndmsg.msgtext,str3);

 if(msgsnd(msgid,&sndmsg,sizeof(str3)+1,0) == -1){
 printf("msgsnd error!\n");
 exit(254);
 }

 if(status = msgrcv(msgid,&rcvmsg,80,333,IPC_NOWAIT) == -1){
 printf("msgrcv error!\n");
 exit(254);
 }

 printf("The received message:%s.\n",rcvmsg.msgtext);
 msgctl(msgid,IPC_RMID,0);
 exit(0);
}

