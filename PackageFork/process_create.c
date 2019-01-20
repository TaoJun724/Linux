#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>



typedef void(*FUNC)(char*);//定义一个函数指针FUNC

void func(char* arg)
{
  printf("%s,child pid id %d,father pid is %d\n",arg,getpid(),getppid());
  sleep(5);
  return ;
}


void process_create(pid_t* pid,void* func,char* arg)
{
  *pid = fork();
  pid_t id;
  if(*pid < 0)
  {
    perror("fork");
    return ;
  }
  else if(*pid == 0)
  {
    FUNC funct = (FUNC)func;
    //设置一个函数指针funct并将func的地址赋值给它
    (*funct)(arg);//调用函数指针指向的函数，参数为arg
    exit(0);
  }
  else 
  {
    id = waitpid(-1,NULL,0);
    printf("wait child successful!child id is %d\n",id);
    return ;
  }
  return ;
}

int main()
{
  pid_t pid;
  process_create(&pid,func,"haha");
  return 0;
}
