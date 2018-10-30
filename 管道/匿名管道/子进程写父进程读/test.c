#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


int main()
{
  int fds[2];
  int p = pipe(fds);
  if(p < 0)
  {
    perror("pipe");
    return 1;
  }
  pid_t id =fork();
  if(id == 0)//子进程写
  {
   close(fds[0]);
   write(fds[1],"haha",4);
   close(fds[1]);
   exit(EXIT_SUCCESS);
  }
  else if (id > 0){
    //父进程
    close(fds[1]);
    char buf[12]={0};
    read(fds[0],buf,12);
    printf("buf=%s\n",buf);
  }
  return 0;
}
