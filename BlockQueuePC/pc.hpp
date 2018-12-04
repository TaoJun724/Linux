#ifndef __PC_HPP__
#define __PC_HPP__ 

#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<queue>
#include<time.h>
#include<stdlib.h>

using namespace std;



class BlockQueue{
  private:
    int _cap;
    queue<int> bq;
    pthread_mutex_t lock;
    pthread_cond_t cond_p;//queue empty
    pthread_cond_t cond_c;//queue full

    int water_line;
  private:
    void LockQueue(){
      pthread_mutex_lock(&lock);
    }

    void UnlockQueue(){
      pthread_mutex_unlock(&lock);
    }

    void ProductWait(){
      pthread_cond_wait(&cond_p,&lock);
    }

    void ConsumeWait(){
      pthread_cond_wait(&cond_c,&lock);
    }

    bool IsEmpty(){
      return bq.size() == 0 ? true : false;
    }

    bool IsFull(){
      return bq.size() == _cap ? true : false;
    }

    void ConsumeSignal(){
      pthread_cond_signal(&cond_c);
    }

    void ProductSignal(){
      pthread_cond_signal(&cond_p);
    }

    bool IsHighWaterLine(){
      return bq.size() > water_line ? true : false;
    }

  public:
    BlockQueue(int cap):_cap(cap),water_line(_cap*2/3)
  {
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond_p,NULL);
    pthread_cond_init(&cond_c,NULL);
  }

  void PushData(const int &data)
  {
    LockQueue();
    while(IsFull()){
      ProductWait();
    }
    bq.push(data);
    if(IsHighWaterLine()){
      ConsumeSignal();
    }
    UnlockQueue();
  }


  void PopData(int &data)
  {
   LockQueue();
   while(IsEmpty()){
      ProductSignal();
      ConsumeWait();
    }
    data = bq.front();
    bq.pop();
    UnlockQueue();
  }

  ~BlockQueue(){
   pthread_mutex_destroy(&lock);
   pthread_cond_destroy(&cond_p);
   pthread_cond_destroy(&cond_c);
  }
};
#endif 
