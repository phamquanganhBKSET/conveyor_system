#include <iostream>
#include <stdlib.h>
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

void Worker::rightPickUp(int i, TYPE* components) {
	this->rightPick = true;
	components[i] = BLANK;
	printf("\nWorker %d: Right arm is picking up the component...\n", i);

	// Trả giá trị cho 1 chân GPIO ở đây báo hiệu cho cánh tay phải gắp




	sleep(PICK_TIME);
	printf("\nWorker %d: Right arm done pick up\n", i);
};

void Worker::leftPickUp(int i, TYPE* components) {
	this->leftPick = true;
	components[i] = BLANK;
	printf("\nWorker %d: Left arm is picking up the component...\n", i);

	// Trả giá trị cho 1 chân GPIO ở đây báo hiệu cho cánh tay trái gắp




	sleep(PICK_TIME);
	printf("\nWorker %d: Left arm done pick up\n", i);
};

void Worker::assembleProduct(int i) {
	this->assemble = true;
	printf("\nWorker %d: Assembling product...\n", i);

	// Trả tín hiệu cho 2 chân GPIO ở đây báo hiệu cho 2 cánh tay lắp sản phẩm




	sleep(ASSEMBLE_TIME);
	printf("\nWorker %d: Done assemble product\n", i);
	sleep(RETURN_TIME);
	printf("\nWorker %d: The product was returned to the other converor belt!\n", i);
	Worker::numberProduct++;
};

void Worker::alarm() {
	// Delay ở đây 




	// Kiểm tra alarm ở đây 



	
}

void Worker::copy(Worker worker) {
	this->wait = worker.wait;
	this->rightPick = worker.rightPick;
	this->leftPick = worker.leftPick;
	this->assemble = worker.assemble;
}