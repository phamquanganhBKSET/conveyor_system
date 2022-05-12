#ifndef WORKER_H
#define WORKER_H

#include "GlobalConstant.h"
#include "Functions.h"
#include "Sensor.h"
#include "GPIO.h"

class Worker {

private:
	STATUS status;
	bool wait;
	bool rightPick;
	bool leftPick;
	bool assemble;

public:
	static int numberProduct;

	Worker();

	~Worker();

	STATUS getStatus();

	bool getWait();

	bool getRightPick();

	bool getLeftPick();

	bool getAssemble();

	void setStatus(STATUS status);

	void setWait(bool wait);

	void setRightPick(bool rightPick);

	void setLeftPick(bool leftPick);

	void setAssemble(bool assemble);

	void rightPickUp(int i, TYPE* components, TYPE component);

	void leftPickUp(int i, TYPE* components, Worker* worker, TYPE component);

	void assembleProduct(int i, TYPE* components, Worker* worker);

	void copy(Worker worker);
};

#endif