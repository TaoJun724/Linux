#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main()
{
  int fd = open("mypipe",O_WRONLY);
  char buf[1024];  
  while(1){
    buf[0]=0;
    printf("Please Enter# ");
    fflush(stdout);
    ssize_t s =read(0,buf,sizeof(buf)-1);
    if(s >0 ){
        buf[s] = 0;
        write(fd,buf,strlen(buf));
    }else if(s <= 0)
    {
    perror("read");
    exit(1);
    }

    }
  close(fd);
  return 0;
}

