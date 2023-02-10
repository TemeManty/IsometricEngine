#include <iostream>

#include "input.h"
#include <GLFW/glfw3.h>
#include "GameEngine/GameEngine.h"
#include "GameEngine/entity.h"

namespace input {
	float moveSpeed = 0.05;



	void scrollWheel(GLFWwindow* window, double xoffset, double yoffset){
		GameEngine::Camera::moveCamera(0, 0, static_cast<float>(yoffset * 0.01));
	}
	void setup(){
		glfwSetScrollCallback(GameEngine::window::window, scrollWheel);
	}

	void handleInput(){

		entity::player* player = GameEngine::World::getPlayer();

		//move camera
		if(glfwGetKey(GameEngine::window::window, GLFW_KEY_W) == GLFW_PRESS){
			//GameEngine::Camera::moveCamera(- moveSpeed, - moveSpeed, 0);
			player -> x -= moveSpeed;
			player -> y -= moveSpeed;
		}

		if(glfwGetKey(GameEngine::window::window, GLFW_KEY_A) == GLFW_PRESS){
			//GameEngine::Camera::moveCamera(moveSpeed, -moveSpeed, 0);
			player -> x += moveSpeed;
			player -> y -= moveSpeed;
		}
		if(glfwGetKey(GameEngine::window::window, GLFW_KEY_S) == GLFW_PRESS){
			//GameEngine::Camera::moveCamera(moveSpeed, moveSpeed, 0);
			player -> x += moveSpeed;
			player -> y += moveSpeed;
		}
		if(glfwGetKey(GameEngine::window::window, GLFW_KEY_D) == GLFW_PRESS){
			//GameEngine::Camera::moveCamera(-moveSpeed, moveSpeed, 0);
			player -> x -= moveSpeed;
			player -> y += moveSpeed;
		}

		if(glfwGetKey(GameEngine::window::window, GLFW_KEY_Q) == GLFW_PRESS){
			
		}
	}
}