#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include "Worker.h"

using namespace std;

int Worker::numberProduct;

Worker::Worker() {
	wait = false;
	rightPick = false;
	leftPick = false;
	assemble = false;
}

Worker::~Worker() {

}

bool Worker::getWait() {
	return this->wait;
};

bool Worker::getRightPick() {
	return this->rightPick;
};

bool Worker::getLeftPick() {
	return this->leftPick;
};

bool Worker::getAssemble() {
	return this->assemble;
};

void Worker::setWait(bool wait) {
	this->wait = wait;
};

void Worker::setRightPick(bool rightPick) {
	this->rightPick = rightPick;
};

void Worker::setLeftPick(bool leftPick) {
	this->leftPick = leftPick;
};

void Worker::setAssemble(bool assemble) {
	this->assemble = assemble;
};

void Worker::rightPickUp(int i, TYPE* components, TYPE component, uint8_t pout) {
	this->rightPick = true;
	components[i] = BLANK;
	printf("\nWorker %d: Right arm is picking up component %s\n", i, toString(component).c_str());

	

	/*
	* Write GPIO value
	*/
	GPIO::GPIOWrite(pout, HIGH);



	sleep(PICK_TIME);
	printf("\nWorker %d: Right arm done pick up component %s\n", i, toString(component).c_str());
};

void Worker::leftPickUp(int i, TYPE* components, Worker* worker, TYPE component, uint8_t pout) {
	this->leftPick = true;
	components[i] = BLANK;
	printf("\nWorker %d: Left arm is picking up component %s\n", i, toString(component).c_str());



	/*
	* Write GPIO value
	*/
	GPIO::GPIOWrite(pout, HIGH);



	sleep(PICK_TIME);
	worker[i].setStatus((STATUS) component);
	printf("\nWorker %d: Left arm done pick up component %s\n", i, toString(component).c_str());
};

void Worker::assembleProduct(int i, TYPE* components, Worker* worker, uint8_t pout[2]) {
	this->assemble = true;
	printf("\nWorker %d: Assembling product...\n", i);

	sleep(ASSEMBLE_TIME);
	worker->setStatus(PRODUCT);
	printf("\nWorker %d: Done assemble product\n", i);

	sleep(RETURN_TIME);
	for (int i = 0; i < NUMBER_SLOTS; i++)
	{
		if (components[i] == BLANK)
		{
			components[i] = TYPE_P;
			break;
		}
	}
	worker->setStatus(NONE);
	printf("\nWorker %d: Returning product...\n", i);
	Worker::numberProduct++;
};

void Worker::copy(Worker worker) {
	this->wait = worker.wait;
	this->rightPick = worker.rightPick;
	this->leftPick = worker.leftPick;
	this->assemble = worker.assemble;
}

STATUS Worker::getStatus() {
	return this->status;
}

void Worker::setStatus(STATUS status) {
	this->status = status;
}
