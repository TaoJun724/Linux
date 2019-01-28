#include"pc.hpp"

int num = 20;


void *Product(void *arg)
{
  RingQueue *r = (RingQueue *)arg;
  srand((unsigned long)time(NULL));
  while(1){
    int data = rand()%100 + 1;
    r->PushData(data);
    sleep(1);
  }
}

void *Custsume(void *arg)
{
  RingQueue *r = (RingQueue *)arg;
  int data;
  while(1){
    r->PopData(data);
  }
}

int main()
{
  RingQueue *r = new RingQueue(num);
  pthread_t p,c;
  pthread_create(&p,NULL,Product,(void *)r);
  pthread_create(&c,NULL,Custsume,(void *)r);


  pthread_join(p,NULL);
  pthread_join(c,NULL);

  delete(r);
}
