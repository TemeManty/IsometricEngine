#include <iostream>

#include <chrono>

#include "timer.h"

Timer::Timer(int time, int prec){
	counter = 0;

	timePrec = prec;

	if(time == 0){

	}else{
		timer = time;
		begin = std::chrono::high_resolution_clock::now();
	}
}

void Timer::tick(){
	counter++;
	end = std::chrono::high_resolution_clock::now();
	if(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() > timer){
		if(printMessageToScreen){
			std::cout << counter << " " << message << " " << timeGone() << std::endl;
		}else{
			std::cout << counter << " ticks in: " << timeGone() << std::endl;
		}
		begin = end;
		counter = 0;	
	}
}

void Timer::start(){
	begin = std::chrono::high_resolution_clock::now();
}

void Timer::stop(){
	end = std::chrono::high_resolution_clock::now();

	if(printMessageToScreen){
		std::cout << message << timeGone() << std::endl;
	}else if(printTimeToScreen){
		std::cout << "ms: " << timeGone() << std::endl;
	}
}

void Timer::setPrint(bool mes, bool time, int prec){
	if(mes){
		printMessageToScreen = true;
	}else{
		printMessageToScreen = false;
	}

	if(time){
		printTimeToScreen = true;
	}else{
		printTimeToScreen = false;
	}

	
}

void Timer::printMessage(const char* text){
	message = text;
}

int Timer::timeGone(){
	switch(timePrec){
		case TIMER_NS:
			return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
			break;
		case TIMER_MS:
			return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
			break;
		case TIMER_S:
			return std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
			break;
		default:
			return 0;
	}
}