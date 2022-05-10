#include <iostream>
#include <unistd.h>
#include <random>
#include "GlobalConstant.h"
#include "Conveyor.h"

using namespace std;

int random(int range_from, int range_to) {
  random_device                 rand_dev;
  mt19937                       generator(rand_dev());
  uniform_int_distribution<int> distr(range_from, range_to);
  return distr(generator);
}

void shiftRight(TYPE* components, int slots, TYPE component) {
  for (int i = slots - 1; i >= 0; i--)
  {
    components[i] = components[i-1];
  }
  components[0] = component;
}

string toString(TYPE component) {
  switch(component) {
    case TYPE_A: {
      return "A";
    }

    case TYPE_B: {
      return "B";
    }

    case BLANK: {
      return " ";
    }
  }
  return " ";
}

int main(int argc, char const *argv[])
{
  Conveyor conveyor;
  Sensor sensor;
  Worker worker;

  TYPE components[NUMBER_SLOTS];

  for (int i = 0; i < 20; i++)
  {
    TYPE component = (TYPE)random(0, 2);
    shiftRight(components, NUMBER_SLOTS, component);
    sleep(1.0/SPEED);
    cout << "\n\nConveyor: " << endl;
    cout << "|";
    for (int i = 0; i < NUMBER_SLOTS; i++)
    {
      cout << toString(components[i]) << "|";
    }

  }
  cout << endl;


  return 0;
}