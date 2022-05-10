#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Conveyor.h"

using namespace std;

Conveyor::Conveyor() {
  this->speed = SPEED;
  this->stop = false;
}

Conveyor::~Conveyor() {

};

void* Conveyor::workerRun(void* args) {
  thread_args *thread_arg = (thread_args*) args;

  do {

    here:
    if (thread_arg->sensor->workerStatus == NONE)
    {

      here1:
      if (thread_arg->sensor->componentType == TYPE_A)
      {
        thread_arg->worker->leftPickUp();

        here2:
        if (thread_arg->sensor->componentType == TYPE_B)
        {
          thread_arg->worker->rightPickUp();
          thread_arg->worker->assembleProduct();
          thread_arg->worker->returnProduct();
        }
        else
        {
          goto here2;
        }
      }
      else if (thread_arg->sensor->componentType == TYPE_B)
      {
        thread_arg->worker->leftPickUp();

        here3:
        if (thread_arg->sensor->componentType == TYPE_A)
        {
          thread_arg->worker->rightPickUp();
          thread_arg->worker->assembleProduct();
          thread_arg->worker->returnProduct();
        }
        else
        {
          goto here3;
        }
      }
      else
      {
        goto here1;
      }
    }
    else
    {
      goto here;
    }
  } while(this->stop != true)

  pthread_exit(NULL);
}

void Conveyor::run() {
  // Create n threads for n workers
  pthread_t tid[NUMBER_WORKERS];
  thread_args thr[NUMBER_WORKERS];

  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    thr[i]->worker = &this->worker[i];
    thr[i]->sensor = &this->sensor[i];
  }

  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    int ret = pthread_create(&(tid[i]), NULL, workerRun, (&thr[i]));
    if (ret != 0)
    {
      printf("Thread [%d] created error\n", i);
    }
  }

  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    pthread_join(tid[i], NULL);
  }

};

void Conveyor::stop() {
  this->stop = true;
}

void Conveyor::getStop() {
  return this->stop;
}