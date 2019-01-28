#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<string>


pthread_mutex_t mutex;
pthread_cond_t cond;

using namespace std;



void *rout1(void *arg)
{
  string t1 = (char *)arg;
  while(1){
    pthread_cond_wait(&cond,&mutex);
    cout<<t1<<"  is running.."<<endl;
  }

}
void *rout2(void *arg)
{
  while(1){
    pthread_cond_signal(&cond);
    sleep(2);
  }
}

int main()
{
  pthread_mutex_init(&mutex,NULL);

  pthread_cond_init(&cond,NULL);

  pthread_t t1,t2;

  pthread_create(&t1,NULL,rout1,(void *)"thread 1");
  pthread_create(&t2,NULL,rout2,(void *)"thread 2");

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);



  pthread_mutex_destroy(&mutex);

  pthread_cond_destroy(&cond);
  return 0;
}

