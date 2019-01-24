#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define NUM 128



int main()
{
  int fds[2];//文件描述符数组，fd[0]表示读端，fd[1]表示写端。

  int p = pipe(fds);

  //创建管道
  if( p < 0 ){
    printf("创建管道失败\n");
    exit(1);
  }

  //从键盘输入读取数据
  while(1){

  char buf[NUM] = {0}; 
    ssize_t s1 = read(0,buf,sizeof(buf)-1);
    if(s1<0){
      perror("read");
      exit(1);
    }
    buf[s1] = 0;
  //写进管道
   write(fds[1],buf,strlen(buf));
  


  
  
  //从管道中读取
  ssize_t s2 =read(fds[0],buf,sizeof(buf)-1);
  buf[s2] = 0;
  //输出到屏幕上
  write(1,buf,strlen(buf));
  


   }
  return 0;
}
