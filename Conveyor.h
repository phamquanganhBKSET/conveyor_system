#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "GlobalConstant.h"
#include "Worker.h"
#include "Sensor.h"
#include "Functions.h"

class Conveyor {
private:
  int speed; // Number of components that are sent to the conveyor per second

public:
  static bool stop;

  static TYPE components[NUMBER_SLOTS];

  static Sensor sensor[NUMBER_WORKERS];

  static Worker worker[NUMBER_WORKERS];

  Conveyor();

  ~Conveyor();

  static void *workerRun(void* args);

  static void* genComponent(void* components);

  static void updateSensorData();

  static void* alarm(void* args);

  void run();
};

#endif