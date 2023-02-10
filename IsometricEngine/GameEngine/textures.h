#pragma once
#include <GL/gl.h>

#define MIPMAP_LEVEL 0
#define FILTER GL_NEAREST

#define BLOCK_TEXTURE 0
#define ENTITY_TEXTURE 1



namespace textures {

	class TexUnit{
	public:
		TexUnit(int width, int height, int numberOfTextures);

		float loadTexture(const char* fileName);

	private:
		void newTextureUnit(int width, int height, int numberOfTextures);

		GLuint texture;

		int textureUnit;
		static int textureUnitCounter;

		int textureIndexCounter;
	};

	class Texture{
	public:
		Texture(float textureIndex);
		
		float index();

	private:
		float textureIndex;
	};


	namespace {
		int blockTextureUnit;
		GLuint blockTextures;
		int blockTextureArrayIndex = 1; //set texture array index to 1 leaving 0 empty for transparent blocks

		int entityTextureUnit;
		GLuint entityTextures;
		int entityTextureArrayIndex = 1;

		int textureUnitCounter = 0;

		void loadTextureToArray(const char* fileName, GLuint texture, int arrayIndex);
	}
}