#include"ThreadPool.hpp"

#define NUM 5

int Add(int x,int y)
{
  return x + y;
}

int main()
{
  ThreadPool *tp =new ThreadPool(NUM);
  tp -> InitThreadPool();

  int count =1;
  int i = 0;
  for(;i<10;i++){
    sleep(1);
    Task t(count,count-1,Add);
    tp->AddTask(t);
    count++;
  }
  return 0;
}
