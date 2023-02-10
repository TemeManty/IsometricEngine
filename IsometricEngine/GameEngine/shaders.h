#pragma once
#include <GL/gl.h>

#define BLOCK_SHADER 0
#define ENTITY_SHADER 1

namespace shaders {

	void createShaders();

	void useShader(int shader);

	void writeUniforms();

	namespace {
		GLuint blockShaderID;

		GLint blockCameraUniform;
		GLint blockRenderDistanceUniform;
		GLint blockTextureArrayUniform;

		GLuint entityShaderID;

		GLint entityCameraUniform;
		GLint entityRenderDistanceUniform;
		GLint entityTextureArrayUniform;


		unsigned int newShader(const char* fileName, GLenum shaderType);
		void createBlockShader();
		void createEntityShader();
	}
}