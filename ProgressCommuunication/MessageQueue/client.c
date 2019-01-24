#include"comm.h"


int main()
{
  int msgid = GetMsgQueue();
  

  char buf[1028];
  while(1){
    buf[0] = 0;
    printf("Please Enter# ");
    fflush(stdout);
    ssize_t s =read(0,buf,sizeof(buf));
    if(s>0){
      buf[s-1]= 0;
      SendMsg(msgid,CLIENT_TYPE,buf);
      printf("send done ,wait ....\n");
    }


    RecvMsg(msgid,SERVER_TYPE,buf);
    printf("send# %s\n",buf);
  }
  return 0;
}
