# The compiler: gcc for C program, define as g++ for C++
CC = g++

# Compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -Wall -g

# The build target
TARGET = main

# Targets needed to bring the executable up to date
all: main.o Conveyor.o Sensor.o Worker.o Functions.o GPIO.o
	$(CC) $(CFLAGS) -pthread -o $(TARGET) main.o Conveyor.o Sensor.o Worker.o Functions.o GPIO.o

main.o: main.cpp Conveyor.h GlobalConstant.h Sensor.h Worker.h GPIO.h
	$(CC) $(CFLAGS) -pthread -o main.o -c main.cpp

Conveyor.o: Conveyor.h Sensor.h Worker.h GlobalConstant.h Functions.h GPIO.h
	$(CC) $(CFLAGS) -pthread -o Conveyor.o -c Conveyor.cpp

Sensor.o: Sensor.h GlobalConstant.h
	$(CC) $(CFLAGS) -pthread -o Sensor.o -c Sensor.cpp

Worker.o: Worker.h Sensor.h GlobalConstant.h Functions.h GPIO.h
	$(CC) $(CFLAGS) -pthread -o Worker.o -c Worker.cpp

Functions.o: GlobalConstant.h Conveyor.h Functions.h
	$(CC) $(CFLAGS) -pthread -o Functions.o -c Functions.cpp

GPIO.o: GPIO.h
	$(CC) $(CFLAGS) -pthread -o GPIO.o -c GPIO.cpp

run:
	chmod +x main
	./main

clean:
	rm -r main main.o Conveyor.o Sensor.o Worker.o Functions.o GPIO.o