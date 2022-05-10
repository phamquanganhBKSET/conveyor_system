#ifndef SENSOR_H
#define SENSOR_H

#include "GlobalConstant.h"

class Sensor {

private:
  STATUS workerStatus;
  TYPE componentType;

public:
  Sensor();

  ~Sensor();
  
  STATUS getWorkerStatus();

  TYPE getComponentType();

  void setWorkerStatus(STATUS workerStatus);

  void setComponentType(TYPE componentType);

  void checkWorkerStatus();

  void chekComponentType();
};

#endif