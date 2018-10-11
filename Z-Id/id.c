#include<stdio.h>     
#include<stdlib.h>
#include<unistd.h>

 int main()
{
    pid_t pid = fork();
    if(pid < 0){ 
        perror("fork");                                                         
        return 1;
    }else if(pid > 0){
        printf("parent : %d\n", getpid());
        sleep(30);
    }else{
        printf("child : %d\n",getpid());
        sleep(5);
    }   
}

