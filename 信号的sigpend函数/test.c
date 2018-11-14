#include<stdio.h>
#include<signal.h>
#include<unistd.h>


void printsigset(sigset_t *set)
{
  int i = 0;
  for(;i<32;i++)
  {
    if(sigismember(set,i))
    {
      putchar('1');
    }
    else{
      putchar('0');
    }
  }
  puts("");

}

int main()
{
   sigset_t s,p;//定义信号集对象，并清空初始化
   sigemptyset(&s);
   sigaddset(&s,SIGQUIT);
   sigprocmask(SIG_BLOCK,&s,NULL);//设置阻塞信号集，阻塞SIGQUIT信号
   while(1){
     sigpending(&p);//获取未决信号集
     printsigset(&p);
     sleep(1);
   }
}
