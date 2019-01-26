#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_alrm(int signo)
{

}


unsigned int mysleep(unsigned int nsecs)
{
  struct sigaction new,old;
  unsigned int unslept = 0;
  new.sa_handler  = sig_alrm;
  sigemptyset(&new.sa_mask);
  new.sa_flags = 0;
  sigaction(SIGALRM,&new,&old);
  alarm(nsecs);
  pause();
  unslept=alarm(0);
  sigaction(SIGALRM,&old,NULL);
  unslept;
}


int main()
{
  while(1){
    mysleep(2);
    printf("2 seconds passed\n");
  }
}
