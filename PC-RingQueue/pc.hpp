#ifndef __PC_HPP___
#define __PC_HPP__


#include<iostream>
#include<queue>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>
#include<vector>
#include<semaphore.h>



using namespace std;



class RingQueue{
  private:
    vector<int> ring;
    int _cap;
    sem_t blank_sem;
    sem_t data_sem;

    int p_step;
    int c_step;
  private:
    void P(sem_t &sem)
    {
      sem_wait(&sem);
    }

    void V(sem_t &sem)
    {
      sem_post(&sem);
    }

  public:
    RingQueue(int cap):_cap(cap),ring(cap)
  {
    p_step = 0;
    c_step = 0;
    sem_init(&blank_sem,0,cap);
    sem_init(&data_sem,0,0);
  }

  void PushData(const int &data)
  {
    P(blank_sem);
    ring[p_step] = data;
    cout<<"product finish,data is :"<<data<<endl;
    V(data_sem);
    p_step++;
    p_step %= _cap;
  }

  void PopData(int &data)
  {
    P(data_sem);
    data = ring[c_step];
    cout<<"consume finish ,data is "<<data<<endl;
    V(blank_sem);
    c_step++;
    c_step %= _cap;
  }

  ~RingQueue()
  {
    sem_destroy(&blank_sem);
    sem_destroy(&data_sem);
  }
};


#endif 
