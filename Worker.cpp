#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "Worker.h"

using namespace std;

Worker::Worker() {
	wait = false;
	rightPick = false;
	leftPick = false;
	assemble = false;
	numberProduct = 0;
}

Worker::~Worker {

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

int Worker::getNumberProduct() {
	return this->numberProduct;
};

void Worker::increaseNumberProduct() {
	this->numberProduct++;
};

void Worker::setNumberProduct(bool numberProduct) {
	this->numberProduct = numberProduct;
};

void Worker::setWait(bool wait) {
	this->wait = wait;
};

void Worker::setRightPick(bool rightPick) {
	this->pick = pick;
};

void Worker::setLeftPick(bool leftPick) {
	this->pick = pick;
};

void Worker::setAssemble(bool assemble) {
	this->assemble = assemble;
};

void Worker::rightPickUp() {
	this->rightPick = true;
	cout << "\nRight arm is picking up the component..." << endl;

	// Trả giá trị cho 1 chân GPIO ở đây báo hiệu cho cánh tay phải gắp




	sleep(PICK_TIME);
	cout << "Done pick up!" << endl;
};

void Worker::leftPickUp() {
	this->leftPick = true;
	cout << "\nLeft arm is picking up the component..." << endl;

	// Trả giá trị cho 1 chân GPIO ở đây báo hiệu cho cánh tay trái gắp




	sleep(PICK_TIME);
	cout << "Done pick up!" << endl;
};

void Worker::assembleProduct() {
	this->assemble = true;
	cout << "\nWorker is assemblling the product..." << endl;

	// Trả tín hiệu cho 2 chân GPIO ở đây báo hiệu cho 2 cánh tay lắp sản phẩm




	sleep(ASSEMBLE_TIME);
};

void Worker::returnProduct() {
	sleep(RETURN_TIME);
	cout << "\nThe product was returned to the other converor belt!" << endl;
	increaseNumberProduct();
};

void Worker::alarm() {
	// Delay ở đây 




	// Kiểm tra alarm ở đây 



	
}