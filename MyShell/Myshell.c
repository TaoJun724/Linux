#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/times.h>
#include<wait.h>
#include<string.h>
#include<unistd.h>
#include<pwd.h>

#define NUM 128
#define MAX 128
int main()
{
  while(1)
  {
     char * myargv[NUM];
     char cmd[MAX];
     printf("[myshell@localhost  myshell]#");
     //shurumingling
     fgets(cmd,sizeof(cmd),stdin);
     cmd[strlen(cmd)-1]=0;
     int i = 0;
     myargv[i++]=strtok(cmd," ");
     char* ret =NULL;
     while(ret==strtok(NULL," "))
     {
        myargv[i++]=ret;
     }
     myargv[i]=NULL;
 //    int j=0;
//     for( ; j<i;j++ )
//     {
//       printf("%s\n",myargv[j]);
//     }
    pid_t id =fork();
    if(id<0)
    {
      perror("use fork");
      exit(1);
    }
    else if(id == 0)
    {
         //child 
      execvp(myargv[0],myargv);
      exit(1);
    }
    else 
    {
      waitpid(id,NULL,0);
    }
  }
  return 0;
}
