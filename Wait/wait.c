#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>

int main(){                                                                                                                                                             
    pid_t pid=fork();
    if(pid==-1){
        perror("use fork");
        exit(1);
    }   
    else if(pid==0){//child
        sleep(5);
        exit(10);
    }   
    else{//parent
        int st;//status
        int ret=wait(&st);
        if(ret>0&&(st&0X7F)==0)
            printf("child exit code is [%d]\n",(st>>8)&0XFF);
         else
            printf("sig code is[%d]\n",st&0X7F);
    }       
} 

