#include <unistd.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX 1024
#define NUM 1024

char* myargv[NUM];

void do_parse(char *cmd)//解析命令行
{
  int i = 0;
  myargv[i++] = strtok(cmd," ");
  char *ret = NULL;
  while(ret == strtok(NULL," ")){
    myargv[i++] = ret;
  }
  myargv[i] = NULL;
}

void do_execute()
{
  pid_t id =fork();
  if(id == 0){
    execvp(myargv[0],myargv);
    exit(1);
  }
  else{
    waitpid(id,NULL,0);
  }
}


int main()
{
  char cmd[MAX];
  while(1){
    printf("[嘻嘻桃子@localhost myshell]# ");
    fgets(cmd,sizeof(cmd),stdin);
    cmd[strlen(cmd)-1] = 0;
    do_parse(cmd);//解析命令行
    do_execute();//执行命令
  }
  return 0;
}
