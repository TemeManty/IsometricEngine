#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "shaders.h"

//include for writing uniforms
//should abstract to gameEngine.c++
#include "GameEngine.h"
#include "renderer.h"
#include "textures.h"



namespace shaders{

	void createShaders(){
		createBlockShader();
		createEntityShader();
	}


	void useShader(int shader){
		switch(shader){
			case BLOCK_SHADER:
				glUseProgram(blockShaderID);
				break;
			case ENTITY_SHADER:
				glUseProgram(entityShaderID);
				break;
			default:
				std::cout << "no shader" << std::endl;
		}
	}

	void writeUniforms(){
		//block shader uniforms
		glUseProgram(blockShaderID);
		glUniform3f(blockCameraUniform, renderer::camera::x, renderer::camera::y, renderer::camera::z);
		glUniform1i(blockRenderDistanceUniform, RENDER_DIST);
		glUniform1i(blockTextureArrayUniform, 0);

		//entity shader uniforms
		glUseProgram(entityShaderID);
		glUniform3f(entityCameraUniform, renderer::camera::x, renderer::camera::y, renderer::camera::z);
		glUniform1i(entityRenderDistanceUniform, RENDER_DIST);
		glUniform1i(entityTextureArrayUniform, 1);
	}

	namespace {

		unsigned int newShader(const char* fileName, GLenum shaderType){
			std::ifstream shaderSourceCodeFile;

			shaderSourceCodeFile.open(fileName, std::fstream::in | std::fstream::binary);

			if(!shaderSourceCodeFile){ 
				//failed to open file
				std::cout << "failed to open file " << fileName << std::endl;
				shaderSourceCodeFile.close();
				return 0;
			}else{
				//get file length
				shaderSourceCodeFile.seekg(0, shaderSourceCodeFile.end);
				int sourceCodeFileLength = shaderSourceCodeFile.tellg();
				shaderSourceCodeFile.seekg(0, shaderSourceCodeFile.beg);

				//read the file into buffer
				char* sourceCodeBuffer = new char[sourceCodeFileLength + 1]();
				shaderSourceCodeFile.read(sourceCodeBuffer, sourceCodeFileLength);

				//add string null char at the end
				sourceCodeBuffer[sourceCodeFileLength] = '\0';

				//create new shader from sourceCode
				unsigned int shader;
				shader = glCreateShader(shaderType);
				glShaderSource(shader, 1, &sourceCodeBuffer, NULL);
				glCompileShader(shader);

				//check if the shader compiled
				int isCompiled = 0;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
				if(isCompiled == GL_FALSE){
					//failed to compile
					std::cout << "shader: " << fileName << " failed to compile" << std::endl;

					//get error message,
					int errLength = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errLength);

					char* errLog = new char[errLength];
					glGetShaderInfoLog(shader, errLength, &errLength, &errLog[0]);

					//print source code red and err log to console
					std::cout << sourceCodeBuffer << std::endl;
					std::cout << std::endl << errLog << std::endl;

					delete[] errLog;
				}


				//free the spurce code buffer memory
				delete[] sourceCodeBuffer;
				
				//close file buffer
				shaderSourceCodeFile.close();

				//return the shader
				return shader;
			}
		}

		void createBlockShader(){
			//load new shaders
			unsigned int VertexShader = newShader("GameEngine/Shaders/BlockVertex.shader", GL_VERTEX_SHADER);
			unsigned int FragmentShader = newShader("GameEngine/Shaders/BlockFragment.Shader", GL_FRAGMENT_SHADER);

			//create new program
			blockShaderID = glCreateProgram();

			//attach shaders
			glAttachShader(blockShaderID, VertexShader);
			glAttachShader(blockShaderID, FragmentShader);

			//link and use program
			glLinkProgram(blockShaderID);
			glUseProgram(blockShaderID);

			//delete the shaders
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			//get uniforms
			blockCameraUniform = glGetUniformLocation(blockShaderID, "cameraPos");
			blockRenderDistanceUniform = glGetUniformLocation(blockShaderID, "renderDistance");
			blockTextureArrayUniform = glGetUniformLocation(blockShaderID, "textureArray");
		}

		void createEntityShader(){
			//load new shaders
			unsigned int VertexShader = newShader("GameEngine/Shaders/entityVertex.shader", GL_VERTEX_SHADER);
			unsigned int FragmentShader = newShader("GameEngine/Shaders/entityFragment.Shader", GL_FRAGMENT_SHADER);

			//create new program
			entityShaderID = glCreateProgram();

			//attach shaders
			glAttachShader(entityShaderID, VertexShader);
			glAttachShader(entityShaderID, FragmentShader);

			//link and use program
			glLinkProgram(entityShaderID);
			glUseProgram(entityShaderID);

			//delete the shaders
			glDeleteShader(VertexShader);
			glDeleteShader(FragmentShader);

			//get uniforms
			entityCameraUniform = glGetUniformLocation(entityShaderID, "cameraPos");
			entityRenderDistanceUniform = glGetUniformLocation(entityShaderID, "renderDistance");
			entityTextureArrayUniform = glGetUniformLocation(entityShaderID, "textureArray");
		}

		
	}

}


