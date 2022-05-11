#include <iostream>
#include <unistd.h>
#include "GlobalConstant.h"
#include "Conveyor.h"

using namespace std;

int main(int argc, char const *argv[])
{
  Conveyor conveyor;

  conveyor.run();

  return 0;
}