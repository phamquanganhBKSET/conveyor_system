#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "GlobalConstant.h"

using namespace std;

int random(int range_from, int range_to);

void shiftRight(TYPE* components, int slots, TYPE component);

string toString(TYPE component);

string toString(STATUS status);

#endif