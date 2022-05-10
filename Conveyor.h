#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "GlobalConstant.h"
#include "Worker.h"
#include "Sensor.h"

class Conveyor {
private:
  int speed; // Number of components that are sent to the conveyor per second
  bool stop;
  Worker worker[NUMBER_WORKERS];
  Sensor sensor[NUMBER_WORKERS];

public:
  Conveyor();

  ~Conveyor();

  void *workerRun(void* args);

  void setWorker(Worker* worker);

  void setSensor(Sensor* sensor);

  void run();

  void stop();

  bool getStop();
};

#endif