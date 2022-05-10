#include <iostream>
#include <stdlib.h>
#include "Sensor.h"

using namespace std;

Sensor::Sensor() {
  this->workerStatus = NONE;
  this->componentType = BLANK;
};

Sensor::~Sensor() {

};
  
STATUS Sensor::getWorkerStatus() {
  return this->workerStatus;
};

TYPE Sensor::getComponentType() {
  return this->componentType;
};

void Sensor::setWorkerStatus(STATUS workerStatus) {
  this->workerStatus = workerStatus;
};

void Sensor::setComponentType(TYPE componentType) {
  this->componentType = componentType;
};

void Sensor::checkWorkerStatus() {
  cout << "\nReading worker status...";
  // Đọc giá trị cảm biến cho workerStatus ở đây và trả kết quả vào biến workerStatus








  switch(this->workerStatus) {
    case COMPONENT_A: {
      cout << "Worker is temporarily holding component A!" << endl;
      break;
    }

    case COMPONENT_B: {
      cout << "Worker is temporarily holding component B!" << endl;
      break;
    }

    case NONE: {
      cout << "Worker is not holding any components!" << endl;
      break;
    }
  }
};

void Sensor::chekComponentType() {
  cout << "\nChecking type of component...";
  // Đọc giá trị cảm biến cho componentType ở đây








  switch(this->componentType) {
    case TYPE_A: {
      cout << "Component A!" << endl;
      break;
    }

    case TYPE_B: {
      cout << "Component B!" << endl;
      break;
    }

    case NONE: {
      cout << "NULL slot!" << endl;
      break;
    }
  }
};