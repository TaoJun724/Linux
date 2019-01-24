#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int  main()
{
  char *argv[] = {"ps","-ef",NULL};
  pid_t pid = fork();
  if(pid == 0)
  {
     execvp("ps",argv);

  }
}
