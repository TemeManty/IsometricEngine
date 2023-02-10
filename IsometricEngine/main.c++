#include <iostream>

#include "GameEngine/GameEngine.h"
#include "GameEngine/timer.h"

#include "input.h"
#include "entities.h"


int main(int argc, char const* argv[]){
	
	//setup engine
	if(!GameEngine::init()){
		std::cout << "failed to init engine" << std::endl;
		return -1;
	}else{


		//setup for game
		Timer timer(1000, TIMER_NS);
		input::setup();

		GameEngine::World::setPlayer(new Player);
		


		//start game loop
		while(!GameEngine::window::windowShouldClose()){
			//timer.start();
			timer.tick();
	
			
			input::handleInput();

			GameEngine::tick();
			GameEngine::render();


			//timer.stop();
		}


		return 0;
	}

}