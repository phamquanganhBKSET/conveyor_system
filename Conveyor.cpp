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

uint8_t pout[NUMBER_WORKERS][2] = { // list of pin out
  {7 , 8 }, // left arm and right arm of the first worker
  {11, 12}, // left arm and right arm of the second worker
  {15, 16}
};

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

  for (int i = 0; i < 60; i++)
  {
    TYPE component = (TYPE)random(0, 2);
    shiftRight(components, NUMBER_SLOTS, component);

    cout << "\n\n|==============|Conveyor status|==============|" << endl;
    cout << endl;
    cout << "\n|Status| ";
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

void* Conveyor::alarm(void* args) {
  do {
    sleep(60);
    if (Worker::numberProduct < PERFORMANCE)
    {
      cout << "\t\tALARM: TOO BAD PERFORMANCE!!!!!!!!!!!!!!";
    }
  } while(Conveyor::stop != true);
  pthread_exit(NULL);
}

void* Conveyor::workerRun(void* args) {
  thread_args *thread_arg = (thread_args*) args;

  uint8_t iter = (int)((thread_arg->worker - &Conveyor::worker[0]));

  do {

    main_branch:
    if (thread_arg->sensor->getWorkerStatus() == NONE)
    {

      branch0:
      if (thread_arg->sensor->getComponentType() == TYPE_A)
      {
        thread_arg->worker->leftPickUp(iter, Conveyor::components, Conveyor::worker, TYPE_A, pout[iter][0]);

        branch1:
        if (thread_arg->sensor->getComponentType() == TYPE_B)
        {
          thread_arg->worker->rightPickUp(iter, Conveyor::components, TYPE_B, pout[iter][1]);
          Conveyor::worker[iter].setStatus(FULL);

          thread_arg->worker->assembleProduct(iter, Conveyor::components, thread_arg->worker, pout[iter]);
        }
        else
        {
          goto branch1;
        }
      }
      else if (thread_arg->sensor->getComponentType() == TYPE_B)
      {
        thread_arg->worker->leftPickUp(iter, Conveyor::components, Conveyor::worker, TYPE_B, pout[iter][0]);

        branch2:
        if (thread_arg->sensor->getComponentType() == TYPE_A)
        {
          thread_arg->worker->rightPickUp(iter, Conveyor::components, TYPE_A, pout[iter][1]);
          Conveyor::worker[iter].setStatus(FULL);

          thread_arg->worker->assembleProduct(iter, Conveyor::components, thread_arg->worker, pout[iter]);
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
  pthread_t wktid[NUMBER_WORKERS];
  pthread_t gentid;
  pthread_t altid;

  thread_args thr[NUMBER_WORKERS];

  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    thr[i].worker = &this->worker[i];
    thr[i].sensor = &this->sensor[i];
  }
  

  for (int i = 0; i < 2 * NUMBER_WORKERS - 1; i++)
  {
    /*
     * Enable GPIO pins
     */
    GPIO::GPIOExport(pout[i][0]);
    GPIO::GPIOExport(pout[i][1]);

    /*
     * Set GPIO directions
     */
    GPIO::GPIODirection(pout[i][0], OUT);
    GPIO::GPIODirection(pout[i][1], OUT);

    /*
     * Write GPIO value
     */
     GPIO::GPIOWrite(pout[i][0], LOW);
     GPIO::GPIOWrite(pout[i][1], LOW);
  }


  pthread_create(&altid, NULL, alarm, NULL);
  pthread_create(&gentid, NULL, genComponent, components);
  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    int ret = pthread_create(&(wktid[i]), NULL, workerRun, (&thr[i]));
    if (ret != 0)
    {
      printf("Thread [%d] created error\n", i);
      return;
    }
  }

  pthread_join(altid, NULL);
  pthread_join(gentid, NULL);
  
  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    pthread_join(wktid[i], NULL);
  }

};

void Conveyor::updateSensorData() {
  for (int i = 0; i < NUMBER_WORKERS; i++)
  {
    sensor[i].setComponentType(Conveyor::components[i]);
  }
}