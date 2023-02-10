#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "GameEngine.h"
#include "world.h"
#include "renderer.h"
#include "shaders.h"
#include "textures.h"

namespace GameEngine {
	//initates all parts of engine
	bool init(){
		if(!window::createWindow()){
			std::cout << "window creation failed" << std::endl;
			return false;
		}else{

			//glfw settings
			glfwSwapInterval(0);

			//openGL settings
			std::cout << "openGL version: " << glGetString(GL_VERSION) << std::endl;
			glMatrixMode(GL_MODELVIEW);
			glOrtho(-1, 1, -1, 1, 0, 1);
			glViewport(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
			glClearColor(0.1, 0.1, 0.1, 0);
			glEnable(GL_TEXTURE_2D);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);



			//engine init functions
			shaders::createShaders();
			renderer::VAO::generateVAOs();
			world::loadWorld();

			textures::TexUnit blockTextures(32, 32, 5);
			textures::Texture grassTex(blockTextures.loadTexture("textures/grass.png"));
			textures::Texture uglyTex(blockTextures.loadTexture("textures/ugly.png"));


			textures::TexUnit entityTextures(32, 64, 5);
			textures::Texture entityTex(entityTextures.loadTexture("textures/testEntity.png"));

			


			return true;
		}
	} 

	void tick(){
		world::updateChunks();
		shaders::writeUniforms();
	}

	void render(){
		//clear screen buffers
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		//issue draw calls
		renderer::render();
		
		//swap buffers
		glfwSwapBuffers(window::window);
		
		//poll events
		glfwPollEvents();
	}


	namespace Camera {
		void moveCamera(float dx, float dy, float dz){
			renderer::camera::x += dx;
			renderer::camera::y += dy;
			renderer::camera::z += dz;
		}

		void moveCamera(float dx, float dy){
			renderer::camera::x += dx;
			renderer::camera::y += dy;
		}

		void setCamera(float x, float y, float z){
			renderer::camera::x = x;
			renderer::camera::y = y;
			renderer::camera::z = z;
		}

		void setCamera(float x, float y){
			renderer::camera::x = x;
			renderer::camera::y = y;
		}
	}

	namespace World {
		void setBlock(int x, int y){

		}

		void setPlayer(entity::player* newPlayer){
			world::setPlayer(newPlayer);
		}

		entity::player* getPlayer(){
			return world::getPlayer();
		}
	}





	namespace window {
		GLFWwindow* window;

		//creates new window
		//returns true if window creation was succesful
		//else returns false
		bool createWindow(){
			if(!glfwInit()){
				//failed to init glfw
				std::cout << "could not initiate glfw" << std::endl;
				glfwTerminate();
				return false;
			}else{
				//create window
				window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Isometric", NULL, NULL);
				if(!window){
					//failed to create a window
					std::cout << "could not create window" << std::endl;
					glfwTerminate();
					return false;
				}else{
					//Set openGL context
					glfwMakeContextCurrent(window);

					//init glew
					if(glewInit()){
						std::cout << "failed to init glew" << std::endl;
						glfwTerminate();
						return false;
					}else{
						return true;
					}
				}
			}
		}


		bool windowShouldClose(){
			return glfwWindowShouldClose(window);
		}
	}


}