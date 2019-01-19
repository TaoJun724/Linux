#include <unistd.h>
#include <sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>


#define MAX 1024
#define NUM 1024

char* myargv[NUM];

void do_parse(char *cmd)//解析命令行
{
  int i = 0;
  myargv[i++] = strtok(cmd," ");
  char *ret = NULL;
  while(ret = strtok(NULL," ")){
    myargv[i++] = ret;
  }
  myargv[i] = NULL;
}

void do_execute()
{
  pid_t id =fork();
  if(id == 0)
  {
    int i = 0;
    int flag = 0;
    //判断命令是否含有输入输出重定向
    for(;myargv[i] !=  NULL;i++)
    {
      //输出重定向
      if(strcmp(myargv[i],">") == 0){
        flag = 1;
        break;
      }
      //输入重定向
      
      if(strcmp(myargv[i],"<") == 0){
        flag = 2;
        break;
      }
    }
    //处理输出重定向
    if(flag == 1)
     {
 //      myargv[i] = NULL;
 //      int oldfd = open(myargv[i+ 1],O_WRONLY|O_CREAT,0777);
 //      if(oldfd < 0){
 //        perror("open");
 //        exit(1);
 //      }
 //      close(1);
 //      int newfd = dup(oldfd);  
        
       char* file = myargv[i+1];
       myargv[i] = NULL;
       close(1);
       open(file,O_WRONLY|O_CREAT,0777);   
      }


    //输入重定向
      if(flag == 2)
      {
//        myargv[i] = NULL;
//        int oldfd = open(myargv[i+ 1],O_RDONLY,0644);
//        if(oldfd < 0){
//          perror("open");
//          exit(1);
//        }
//        close(0);
//        int newfd = dup(oldfd);        
//      
            
       char* file = myargv[i+1];
       myargv[i] = NULL;
       close(0);
       open(file,O_WRONLY|O_CREAT,0777);   
      }
    

    execvp(myargv[0],myargv);
    exit(1);
  }



  if(id > 0)
  {
    waitpid(id,NULL,0);
  }
}


int main()
{
  char cmd[MAX];
  while(1){
    
    printf("[嘻嘻桃子@localhost myshell]# ");
    //fgets(cmd,sizeof(cmd),stdin);
     fflush(stdout);
    ssize_t s = read(0,cmd,sizeof(cmd)-1);
    if(s > 0){
      cmd[s-1]=0;
    }
    do_parse(cmd);//解析命令行
    do_execute();//执行命令
  }
  return 0;
}























