#include<iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;
pthread_mutex_t mutex;


void *route(void *arg)
{
  int ticket = 20;
  char *id = (char *)arg;
  while(1){
    pthread_mutex_lock(&mutex);
    if(ticket>0){
      usleep(1000);
      cout<<"id sells thicket"<<ticket<<endl;
      ticket--;
      pthread_mutex_unlock(&mutex);
    }else{
      pthread_mutex_unlock(&mutex);
      break;
    }
  }
}





int main()
{
  pthread_t t1,t2,t3,t4;

  pthread_mutex_init(&mutex,NULL);


  pthread_create(&t1,NULL,route,(void*)"thread 1");
  pthread_create(&t2,NULL,route,(void *)"thread 2");
  pthread_create(&t3,NULL,route,(void *)"thread 3");
  pthread_create(&t4,NULL,route,(void *)"thread 4");

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);

  pthread_mutex_destroy(&mutex);
}
