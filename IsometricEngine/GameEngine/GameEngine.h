#pragma once

#include <GLFW/glfw3.h>
#include "entity.h"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 750

#define RENDER_DIST 16

#define WORLD_HEIGHT 5

namespace GameEngine {
	//setup functions
	bool init();


	//game tick and render calls
	void render();
	void tick();


	namespace Camera {
		void moveCamera(float dx, float dy, float dz);
		void moveCamera(float dx, float dy);
		void setCamera(float x, float y, float z);
		void setCamera(float x, float y);

		void lockCameraToPlayer();
		void unlockCamera();		
	}

	namespace World {
		void setBlock();

		void setPlayer(entity::player* newPlayer);
		entity::player* getPlayer();
	}


	namespace window {
		extern GLFWwindow* window;
		bool createWindow();
		bool windowShouldClose();
	}
}