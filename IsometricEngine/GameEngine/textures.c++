#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "textures.h"

#include <png.h>
#include "lib/lodepng.h"




namespace textures {


	TexUnit::TexUnit(int width, int height, int numberOfTextures){
		newTextureUnit(width, height, numberOfTextures);
		textureIndexCounter = 1;
	}

	int TexUnit::textureUnitCounter = 0;

	void TexUnit::newTextureUnit(int width, int height, int numberOfTextures){
		//generate new texture
		glGenTextures(1, &texture);

		//bind texture
		glActiveTexture(GL_TEXTURE0 + textureUnitCounter);
		glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

		//track texture unit
		textureUnit = textureUnitCounter;
		textureUnitCounter++;

		//allocate memory for textures
		glTexImage3D(GL_TEXTURE_2D_ARRAY, MIPMAP_LEVEL, GL_RGBA, width, height, numberOfTextures,
				 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}

	float TexUnit::loadTexture(const char* fileName){
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		loadTextureToArray(fileName, texture, textureIndexCounter);
		textureIndexCounter++;
		return static_cast<float>(textureIndexCounter - 1);
	}




	Texture::Texture(float i_textureIndex){
		textureIndex = i_textureIndex;


	}

	float Texture::index(){
		return textureIndex;
	}
		



	namespace {

		void loadTextureToArray(const char* fileName, GLuint texture, int arrayIndex){
			//png data
			unsigned width, height;
			std::vector<unsigned char> textureData;

			//read image
			unsigned error = lodepng::decode(textureData, width, height, fileName);

			//check for errors
			if(error){
				std::cout << "error reading png: " << fileName << std::endl;
				std::cout << "error message: "  << error << ": " << lodepng_error_text(error) << std::endl;
			}else{
				//bind texture
				glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

				//load texture to vram
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, MIPMAP_LEVEL, 0, 0, 
					arrayIndex, width, height, 1,
					GL_RGBA, GL_UNSIGNED_BYTE, &textureData[0]);

				//set texture parameters
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, FILTER);//GL_NEAREST
				glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, FILTER);//GL_NEAREST
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		   		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
		}


	}


}