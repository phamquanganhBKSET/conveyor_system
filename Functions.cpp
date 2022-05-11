#include <iostream>
#include <random>
#include "GlobalConstant.h"

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

    case TYPE_P: {
      return "P";
    }
  }
  return " ";
}

string toString(STATUS status) {
  switch(status) {
    case COMPONENT_A: {
      return "A";
    }

    case COMPONENT_B: {
      return "B";
    }

    case NONE: {
      return "N";
    }

    case PRODUCT: {
      return "P";
    }

    case FULL: {
      return "2";
    }
  }
  return " ";
}