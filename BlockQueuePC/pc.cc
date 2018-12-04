#include"pc.hpp"


const int num = 10;


void *Consume(void *arg)
{
  BlockQueue *bqp = (BlockQueue*)arg;
  int data;
  for(;;){
    bqp->PopData(data);
    cout<<"consume data: "<<data<<endl;
  }
}

void *Product(void *arg)
{
  BlockQueue *bqp = (BlockQueue*)arg;
  srand((unsigned long)time(NULL));
  for(;;){
    int data = rand()%100 + 1;
    bqp->PushData(data);
    cout<<"product data  "<<data<<endl;
    usleep(100000);
  }
}


int main()
{
  BlockQueue *bqp = new BlockQueue(num);
  pthread_t c,p;

  pthread_create(&c,NULL,Consume,(void *)bqp);
  pthread_create(&p,NULL,Product,(void *)bqp);

  pthread_join(c,NULL);
  pthread_join(p,NULL);

  delete(bqp);
}
