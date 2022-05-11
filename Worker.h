#ifndef WORKER_H
#define WORKER_H

#include "GlobalConstant.h"
#include "Functions.h"
#include "Sensor.h"

class Worker {

private:
	bool wait;
	bool rightPick;
	bool leftPick;
	bool assemble;

public:
	static int numberProduct;

	Worker();

	~Worker();

	bool getWait();

	bool getRightPick();

	bool getLeftPick();

	bool getAssemble();

	void setWait(bool wait);

	void setRightPick(bool rightPick);

	void setLeftPick(bool leftPick);

	void setAssemble(bool assemble);

	void rightPickUp(int i, TYPE* components, TYPE component);

	void leftPickUp(int i, TYPE* components, TYPE component);

	void assembleProduct(int i);

	void alarm();

	void copy(Worker worker);
};

#endif