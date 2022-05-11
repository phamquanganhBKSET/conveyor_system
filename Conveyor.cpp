#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Conveyor.h"

using namespace std;

bool Conveyor::stop;
TYPE Conveyor::components[NUMBER_SLOTS];
Sensor Conveyor::sensor[NUMBER_WORKERS];
Worker Conveyor::worker[NUMBER_WORKERS];

typedef struct
{
  Worker* worker;
  Sensor* sensor;
} thread_args;

Conveyor::Conveyor() {
  speed = SPEED;

  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    this->sensor[i].setWorkerStatus(NONE);
    this->sensor[i].setComponentType(BLANK);
  }

  for (int i = 0; i < NUMBER_WORKERS; ++i)
  {
    this->worker[i].setWait(false);
    this->worker[i].setRightPick(false);
    this->worker[i].setLeftPick(false);
    this->worker[i].setAssemble(false);
  }
}

Conveyor::~Conveyor() {

};

void* Conveyor::genComponent(void* args) {
  TYPE *components = (TYPE*) args;

  for (int i = 0; i < 50; i++)
  {
    TYPE component = (TYPE)random(0, 2);
    shiftRight(components, NUMBER_SLOTS, component);

    cout << "\n\n|==============|Conveyor status|==============|" << endl;
    cout << endl;
    cout << "         ";
    for (int i = 0; i < NUMBER_WORKERS; i++)
    {
      cout << " " << toString(Conveyor::worker[i].getStatus());
    }
    cout << "\n|Worker| ";
    for (int i = 0; i < NUMBER_WORKERS; i++)
    {
      cout << " " << i;
    }

    cout << "\n|Left  | =====================";
    cout << "\n         |";

    for (int i = 0; i < NUMBER_SLOTS; i++)
    {
      cout << toString(components[i]) << "|";
    }

    cout << endl;
    cout << "|Right | =====================" << endl;
    cout << "|Worker| ";
    for (int i = 0; i < NUMBER_WORKERS; ++i)
    {
      cout << " " << i;
    }
    cout << endl;
    cout << "\n|===|NUMBER OF PRODUCTS: " << Worker::numberProduct << "|===|" << endl;
    updateSensorData();
    sleep(1.0/SPEED);
  }

  cout << endl << endl;
  Conveyor::stop = true;

  pthread_exit(NULL);
}

void* alarm(void* args) {
  // Delay ở đây 




  // Kiểm tra alarm ở đây 



  
}

void* Conveyor::workerRun(void* args) {
  thread_args *thread_arg = (thread_args*) args;

  int iter = (int)((thread_arg->worker - &Conveyor::worker[0]));

  do {

    main_branch:
    if (thread_arg->sensor->getWorkerStatus() == NONE)
    {

      branch0:
      if (thread_arg->sensor->getComponentType() == TYPE_A)
      {
        thread_arg->worker->leftPickUp(iter, Conveyor::components, Conveyor::worker, TYPE_A);

        branch1:
        if (thread_arg->sensor->getComponentType() == TYPE_B)
        {
          thread_arg->worker->rightPickUp(iter, Conveyor::components, TYPE_B);
          Conveyor::worker[iter].setStatus(FULL);

          thread_arg->worker->assembleProduct(iter, Conveyor::components, thread_arg->worker);
        }
        else
        {
          goto branch1;
        }
      }
      else if (thread_arg->sensor->getComponentType() == TYPE_B)
      {
        thread_arg->worker->leftPickUp(iter, Conveyor::components, Conveyor::worker, TYPE_B);

        branch2:
        if (thread_arg->sensor->getComponentType() == TYPE_A)
        {
          thread_arg->worker->rightPickUp(iter, Conveyor::components, TYPE_A);
          Conveyor::worker[iter].setStatus(FULL);

          thread_arg->worker->assembleProduct(iter, Conveyor::components, thread_arg->worker);
        }
        else
        {
          goto branch2;
        }
      }
      else
      {
        goto branch0;
      }
    }
    else
    {
      goto main_branch;
    }
  } while(Conveyor::stop != true);
  cout << "\n|===|NUMBER OF PRODUCTS: " << Worker::numberProduct << "|===|" << endl;

  pthread_exit(NULL);
}

void Conveyor::run() {
  // Create n threads for n workers
  pthread_t tid[NUMBER_WORKERS];
  pthread_t gentid;

  thread_args thr[NUMBER_WORKERS];

  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    thr[i].worker = &this->worker[i];
    thr[i].sensor = &this->sensor[i];
  }

  pthread_create(&gentid, NULL, genComponent, components);
  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    int ret = pthread_create(&(tid[i]), NULL, workerRun, (&thr[i]));
    if (ret != 0)
    {
      printf("Thread [%d] created error\n", i);
      return;
    }
  }

  pthread_join(gentid, NULL);
  
  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    pthread_join(tid[i], NULL);
  }

};

void Conveyor::updateSensorData() {
  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    sensor[i].setComponentType(Conveyor::components[i]);
  }
}