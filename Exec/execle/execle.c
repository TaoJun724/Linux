#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
   char *const envp[] = {"haha","lala",NULL};
   int ret;
   ret = execle("./hello","ls",NULL,envp);

}
