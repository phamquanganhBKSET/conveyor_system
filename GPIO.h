#ifndef GPIO_H
#define GPIO_H

#define IN  0
#define OUT 1

#define LOW  0
#define HIGH 1

class GPIO {

public:
	static int GPIOExport(int pin);

	static int GPIOUnexport(int pin);

	static int GPIODirection(int pin, int dir);

	static int GPIORead(int pin);

	static int GPIOWrite(int pin, int value);
};

#endif