#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
  int fd = open("myfile",O_RDONLY);
  if(fd < 0)
  {
    perror("open");
    exit(1);
  }
  const char* msg = "hello taotao\n";
  char buf[1024];
  while(1)
  {
    ssize_t s = read(fd,buf,strlen(msg));
    if(s > 0)
    {
      printf("%s",buf);
    }else{
      buf[s] = 0;
      break;
    }
  }
  close(fd);
  
}

