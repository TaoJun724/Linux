#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){
    pid_t id=fork();                                                                                                                                                    
    if(id<0){
        perror("use fork");
        exit(1);
    }   
    else if(id==0){//child
        printf("child is run,pid is [%d]\n",getpid());
        sleep(5);
        exit(37);
    }   
    else{//parent
        int st;
        pid_t ret=waitpid(-1,&st,0);//0代表阻塞式
        printf("this is test for waitpid\n");
        if(WIFEXITED(st)&&ret==id)//WIFEXITED判断是否正常返回
            printf("wait child 5s success,child return code is [%d]\n",WEXITSTATUS(st));
            //WEXITSTATUS宏获取退出码
        else{
            printf("wait child failed,return.\n");
            return 1;
        }
    }
    return 0;
}
