#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
  pid_t pid = fork();
  if(pid < 0)
  {
    printf("fork error");
  }
  else if(pid == 0)
  {
    execlp("ps","ps","-ef",NULL);
  }
  else 
  {
    printf("parent process\n");
  }
}
