#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
  
  if(mkfifo("mypipe",0644)<0){
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }
  int fd = open("mypipe",O_RDONLY);
  if(fd <0 ){
    perror("open");
  }
  char buf[1024];
  while(1){
    buf[0] = 0;
    printf("Please  wait......\n");
    ssize_t s =read(fd,buf,sizeof(buf)-1);
    if(s > 0){
      buf[s-1] = 0;
      printf("client say# %s\n",buf);
    }else if(s == 0){
      printf("client quit\n");
      exit(EXIT_SUCCESS);
    }

  }


  close(fd);
  return 0;
}
