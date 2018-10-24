#include"comm.h"



static int CommMsgQueue(int flags)
{
   key_t _key = ftok(PATHNAME,PROJ_ID);
   if(_key < 0)
   {
     perror("ftok");
     return -1;
   }
   int msgid = msgget(_key,flags);
   if(msgid < 0)
   {
     perror("msgget");
   }
   return msgid;  
}

int CreatMsgQueue()
{
 return CommMsgQueue(IPC_CREAT|IPC_EXCL|0666);  
}
int GetMsgQueue()
{
 return CommMsgQueue(IPC_CREAT);
}

int DestoryMsgQueue(int msgid)
{
  if(msgctl(msgid,IPC_RMID,NULL)<0)
  {
    perror("msgctl");
    return -1;
  }
  return 0;
}

int SendMsg(int  msgid ,int type,char *msg)
{
  struct buf message;
  message.mtype = type;
  strcpy(message.mtext,msg);

  if(msgsnd(msgid,(void*)&message,sizeof(message.mtext),0)<0){
   perror("msgsnd");
   return -1;
  }
  return 0;
}

int RecvMsg(int msgid,int type,char out[])
{
  struct buf message;
  if(msgrcv(msgid,(void*)&message,sizeof(message.mtext),type,0)<0){
    perror("msgrve");
    return -1;
  }
  strcpy(out,message.mtext);
  return 0;
}
