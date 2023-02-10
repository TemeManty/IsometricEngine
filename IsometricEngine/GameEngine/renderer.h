#pragma once
#include <GL/gl.h>

#define BLOCK_VAO 0

namespace renderer {

	void render();
	
	namespace camera {
		extern float x;
		extern float y;
		extern float z;
	}

	namespace VAO {
		

		void generateVAOs();
		void deleteVAOs();
		
		void writeBlockData(int chunkX, int chunkY, float* data);
		void writeEntityData(int chunkX, int chunkY, float* data);

		int arrayIndex(int x, int y); //helper function 

		class VAO_CLASS{
		public:
			void generateVAO(unsigned int* indexData, float* vertexData, int shader);
			void allocateDataVBO_f(int attribIndex, int numberOfDataPoints, int dataPointsPerInstance, int div);
			void writeSubDataVBO_f(int attribIndex, int offset, int numberOfDataPoints, float* VBOdata);
			void allocateDataVBO_i(int attribIndex, int numberOfDataPoints, int dataPointsPerInstance, int div);
			void writeSubDataVBO_i(int attribIndex, int offset, int numberOfDataPoints, int* VBOdata);
			void deleteDataVBO();
			void render();
		private:
			GLuint VAO;
			GLuint indexVBO;
			GLuint indicesVBO;
			GLuint dataVBO[5];

			int shaderID;

			int numberOfObjectsToRender;

		};

		extern unsigned int blockIndexData[6];
		extern float blockVertexData[4*4];
		extern unsigned int entityIndexData[6];
		extern float entityVertexData[4*4];
		extern GLint* chunkCoords;
	}
}