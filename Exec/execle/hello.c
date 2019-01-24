#include<unistd.h>
#include<stdio.h>
extern char** environ;

int main()
{
  printf("hello pid = %d\n",getpid());
  int i = 0;
  for(;environ[i] != NULL;i++)
  {
    printf("%s\n",environ[i]);
  }
  return 0;
}
