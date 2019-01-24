#ifndef _COMM_H__
#define _COMM_H__ 


#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define PATHNAME "."
#define PROJ_ID  0x6366 

#define SERVER_TYPE 1
#define CLIENT_TYPE 2



int CreatMsgQueue();
int GetMsgQueue();
int DestoryMsgQueue(int msgid);
int SendMsg(int msgid, int type, char *msg);
int RecvMsg(int msgid, int type , char out[]);

//消息队列结构体
struct  buf{
  long mtype;
  char mtext[1024];
};

#endif 
