#include<unistd.h>
#include<stdio.h>
#include<string.h>

int main()
{
  char bar[102]={'\0'};
  char* lable="|/-\\";
  int i=0;
  while(i<=100)
  {
      bar[i++]='>';
      printf("\033[1;33;40m[%-100s] \033[1;33;40m[%d%%][%c]\r",bar,i,lable[i%4]);
      fflush(stdout);//刷新输出缓冲区
      usleep(10000);
  }
    printf("\n");
}
