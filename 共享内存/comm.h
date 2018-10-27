#ifndef  __COMM_H__
#define  __COMM_H__

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

int creatShm(int size);
int destroyShm(int shmid);
int getShm(int size);




#endif 
