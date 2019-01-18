#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
  pid_t pid;
  pid = fork();
  if(pid < 0)
  {
    printf("error");
    exit(-1);
  }
  else if(pid == 0)
  {
    //子进程
    execl("/bin/ls","ls","-l",NULL);
  }
  else 
  {
    printf("parent process\n");
  }
}
