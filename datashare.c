#include <stdio.h>
#include <pthread.h>

#define THREAD_NUM 2
#define DATA_NUM 10

typedef struct _thread_arg
{
  int thread_no;
  int *data;
  pthread_mutex_t *mutex;
} thread_arg_t;

void thread_func(void *arg)
{
  thread_arg_t* targ = (thread_arg_t *)arg;
  int i,result;

  /*引数データの値に1を加えて配列に格納し直す*/
  for(i=0;i<DATA_NUM;i++){
    /*排他制御開始*/
    pthread_mutex_lock(targ->mutex);
    result = targ->data[i] + 1;
    sched_yield(); //スレッド切り替えチャンスを与える！！？
    targ->data[i] = result;
    pthread_mutex_unlock(targ->mutex);
  }
}

int main()
{
  pthread_t handle[THREAD_NUM];
  thread_arg_t targ[THREAD_NUM];
  int data[DATA_NUM];
  int i;
  pthread_mutex_t mutex;

  /*データの初期化*/
  for(i=0;i<DATA_NUM;i++)data[i] = 0;

  /*mutexハンドルの初期化*/
  pthread_mutex_init(&mutex, NULL);

  for(i=0; i<THREAD_NUM; i++)
  {
    targ[i].thread_no = i;
    targ[i].data = data;
    targ[i].mutex = &mutex;
    pthread_create(&handle[i],
                   NULL,
                   (void*)thread_func,
                   (void*)&targ[i]);
  }
  for(i=0;i<THREAD_NUM;i++)
    pthread_join(handle[i],NULL);

  /*mutexハンドルの破棄*/
  pthread_mutex_destroy(&mutex);

  /*スレッドによる演算の結果出力*/
  for(i=0;i<DATA_NUM; i++)printf("data%d : %d\n",i, data[i]);
  return 0;
}

    
