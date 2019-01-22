#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int Creat_Daemon()
{
  //1.调用umask将文件模式创建屏蔽字设置为0
  umask(0);
  //2.调用fork,父进程退出（exit)
  pid_t id =fork();
  if(id > 0)
  {
    exit(1);
  }
  else if(id == 0)
  {
    //3.创建一个新的会话
    setsid();
  //4.将新建会话的工作目录改为根目录
    if(chdir("/") < 0){
      perror("chdir");
      return;
    }
     //5.关闭从父进程继承来的文件
     close(0);
     close(1);
     close(2);
     //忽略SIGSHLD信号
     signal(SIGCHLD,SIG_IGN);
  }

  
}


  int main()
  {
    Creat_Daemon();
    while(1);
    return 0;
  }
