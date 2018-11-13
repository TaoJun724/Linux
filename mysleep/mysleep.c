#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void  sig_alrm(int signo)
{

}

unsigned int mysleep(unsigned  int  nsecs)
{
  struct sigaction  new,old;
  sigset_t   newmask,oldmask,suspmask;
  unsigned  int unslept = 0;



  new.sa_handler = sig_alrm;
  sigemptyset(&new.sa_mask);
  new.sa_flags = 0;
  sigaction(SIGALRM,&new,&old);//注册信号处理函数


  sigemptyset(&newmask);
  sigaddset(&newmask,SIGALRM);
  sigprocmask(SIG_BLOCK,&newmask,&oldmask);



  alarm(nsecs);//设置闹钟

  suspmask = oldmask ;
  sigdelset(&suspmask,SIGALRM);
  sigsuspend(&suspmask);



  

  unslept = alarm(0);//清空闹钟
  sigaction(SIGALRM,&old,NULL);//恢复信号默认动作
  sigprocmask(SIG_SETMASK,&oldmask,NULL);
  return unslept;
}



int main()
{
  while(1){
    mysleep(1);
    printf("1 seconds passed\n");
  }
  return 0;
}
