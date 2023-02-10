#pragma once
#include <chrono>

#define TIMER_NS 0 //nanoseconds
#define TIMER_MS 1 //milliseconds
#define TIMER_S 2  //seconds

/*
if timer(time == 0) use start() and stop()
else use tick()

setPrint() can disable printing and has to be called to print message
printMessage() set the message to print form counter / message / time
*/
class Timer {
public:
	Timer(int time, int prec); //in ms

	void tick();

	void start();
	void stop();

	void setPrint(bool customMessage, bool time, int timePrecision);
	void printMessage(const char* text);
private:
	bool printMessageToScreen = false;
	bool printTimeToScreen = true;
	const char* message;

	int timePrec;

	std::chrono::high_resolution_clock::time_point begin;
	std::chrono::high_resolution_clock::time_point end;

	int counter;
	int timer;

	int timeGone();
};