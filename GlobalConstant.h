#ifndef GLOBALCONSTANT_H
#define GLOBALCONSTANT_H

#define NUMBER_SLOTS     10   // Number of slots on the conveyor
#define SPEED            1    // Initial speed (speed is number of components that are sent to the conveyor per second)
#define PERFORMANCE      10   // Number of products that are needed to be assembled per minute
#define ASSEMBLE_TIME    2    // Assemble time (seconds)
#define PICK_TIME        1    // Pick up time (seconds)
#define RETURN_TIME      1    // Return product time
#define NUMBER_WORKERS   3    // Number of workers

enum STATUS {
  COMPONENT_A = 1,
  COMPONENT_B = 2,
  NONE        = 0,
  PRODUCT     = 3,
  FULL        = 4
};

enum TYPE {
  TYPE_A = 1,
  TYPE_B = 2,
  BLANK  = 0,
  TYPE_P = 3,
};

#endif