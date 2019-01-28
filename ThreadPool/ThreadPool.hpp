#ifndef __THREADPOLL_HPP__
#define __THREADPOLL_HPP__ 

#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>

using namespace std;


typedef int(*cal_t)(int,int);

class Task{
  private:
    int x;
    int y;
    int z;
    cal_t handler_task;
  public:
    Task(int a,int b,cal_t handler_task_)
    :x(a),y(b),handler_task(handler_task_)
    {

    }

    void Run()
    {
      z = handler_task(x,y);
    }

    void Show()
    {
      cout<<"thread : "<<pthread_self()<<"Task finish,result is : "<<z<<endl;
    }

    ~Task()
    {

    }
};

class  ThreadPool{
   private:
     queue<Task> Task_Queue;
     bool IsStop;
     int ThreadNum;
     pthread_mutex_t lock;
     pthread_cond_t cond;



  private:
    static  void *route(void *arg)
     {
        ThreadPool *tp = (ThreadPool*)arg;
        pthread_detach(pthread_self());
        while(1){
          tp->LockQueue();
          if(tp->IsEmpty()){
              tp->IdleThread();
          }
          Task t = tp->GetTask();
          tp->UnlockQueue();
          
          t.Run();
          t.Show();
        }
     }

     void NoticOneThread()
     {
       pthread_cond_signal(&cond);
     }

     void NoticAllThread()
     {
       pthread_cond_broadcast(&cond);
     }
   public:
     ThreadPool(int num):ThreadNum(num),IsStop(false)
     {}

     void InitThreadPool()
     {
       pthread_mutex_init(&lock,NULL);
       pthread_cond_init(&cond,NULL);
       int i = 0;
      
       
       for(;i<ThreadNum;i++)
       {
          pthread_t tid;
          pthread_create(&tid,NULL,route,(void *)this);
       }
     }

     ~ThreadPool()
     {
          pthread_mutex_destroy(&lock);
          pthread_cond_destroy(&cond);
     }
    

     void LockQueue()
     {
       pthread_mutex_lock(&lock);
     }

     void UnlockQueue()
     {
       pthread_mutex_unlock(&lock);
     }
     
     bool IsEmpty()
     {
       return Task_Queue.size() == 0 ? true : false;
     }

     void AddTask(Task &t)
     {
       if(IsStop)
       {
         UnlockQueue();
         return ;
       }
      Task_Queue.push(t);
      NoticOneThread();
      UnlockQueue();
     }
        
     void IdleThread()
     {
       if(IsStop){
         UnlockQueue();
         ThreadNum--;
         pthread_exit((void *)0);
         cout<<"pthread "<<pthread_self() <<"quit"<<endl;
         return ;
       }
       pthread_cond_wait(&cond,&lock);
     }

     Task GetTask()
     {
       Task t = Task_Queue.front();
       Task_Queue.pop();
       return t;
     }

     void Stop()
     {
       LockQueue();
       IsStop = true;
       UnlockQueue();
       while(ThreadNum > 0){
         NoticAllThread();
       }
     }

};



#endif 
