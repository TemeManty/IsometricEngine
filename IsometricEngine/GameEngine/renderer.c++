#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include "renderer.h"

#include "GameEngine.h"
#include "shaders.h"
#include "world.h"


/*

create transparent blocks their own VAO and draw them last?

*/

renderer::VAO::VAO_CLASS* blockVAO;
renderer::VAO::VAO_CLASS* entityVAO;





namespace renderer {

	void render(){
	
		blockVAO[0].render();
		entityVAO[0].render();
	
	}


	namespace camera {
		float x = 0;
		float y = 0;
		float z = 0.5;
	}

	namespace VAO {
		void generateVAOs(){
			//create block VAOs
			blockVAO = new VAO_CLASS[2];

			//generate new VAO
			blockVAO[0].generateVAO(blockIndexData, blockVertexData, BLOCK_SHADER);
			
			//generate chunkCoords array
			chunkCoords = new int[RENDER_DIST * RENDER_DIST * 3];

			for(int chunkX = 0; chunkX < RENDER_DIST; chunkX++){
				for(int chunkY = 0; chunkY < RENDER_DIST; chunkY++){
					chunkCoords[(arrayIndex(chunkX, chunkY) * 3) + 0] = chunkX;
					chunkCoords[(arrayIndex(chunkX, chunkY) * 3) + 1] = chunkY;
					chunkCoords[(arrayIndex(chunkX, chunkY) * 3) + 2] = WORLD_HEIGHT;
				}
			}

			//chunk data vbo
			blockVAO[0].allocateDataVBO_i(0, RENDER_DIST * RENDER_DIST * 3, 3,
								 CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT);
			blockVAO[0].writeSubDataVBO_i(0, 0, RENDER_DIST * RENDER_DIST * 3, chunkCoords);

			delete[] chunkCoords;

			//block data vbo
			blockVAO[0].allocateDataVBO_f(1, 
				RENDER_DIST * RENDER_DIST * CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * DATA_POINTS_PER_BLOCK,
										DATA_POINTS_PER_BLOCK, 1);



			//entityVAO
			entityVAO = new VAO_CLASS[2];
			entityVAO[0].generateVAO(entityIndexData, entityVertexData, ENTITY_SHADER);

			//allocate entity data
			entityVAO[0].allocateDataVBO_f(0, 
				RENDER_DIST * RENDER_DIST * MAX_NUMBER_OF_ENTITIES_PER_CHUNK * DATA_POINTS_PER_ENTITY, DATA_POINTS_PER_ENTITY,
				 1);

		}

		void deleteVAOs(){

		}

		
		void writeBlockData(int chunkX, int chunkY, float* data){
			blockVAO[0].writeSubDataVBO_f(1, arrayIndex(chunkX, chunkY) * CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * DATA_POINTS_PER_BLOCK, 
				CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * DATA_POINTS_PER_BLOCK, data);
		}

		void writeEntityData(int chunkX, int chunkY, float* data){
			entityVAO[0].writeSubDataVBO_f(0, arrayIndex(chunkX, chunkY) * MAX_NUMBER_OF_ENTITIES_PER_CHUNK * DATA_POINTS_PER_ENTITY, 
											MAX_NUMBER_OF_ENTITIES_PER_CHUNK * DATA_POINTS_PER_ENTITY, data);
		}

		int arrayIndex(int chunkX, int chunkY){
			return chunkX + (chunkY * RENDER_DIST);
		}



		//CLASS
		void VAO_CLASS::generateVAO(unsigned int* indexData, float* vertexData, int shader){
			//generate and bind new vao
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);

			//bind indices
			glGenBuffers(1, &indexVBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indexData, GL_STATIC_DRAW);

			//generate vertex data VBO 
			glGenBuffers(1, &indicesVBO);
			glBindBuffer(GL_ARRAY_BUFFER, indicesVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 4, vertexData, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0); //screen coords
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);

			glEnableVertexAttribArray(1); //texture coords
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

			//set shader
			shaderID = shader;

			//unbind gl objects
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}


		void VAO_CLASS::allocateDataVBO_f(int attribIndex, int numberOfDataPoints, int dataPointsPerInstance, int div){
			//bind VAO
			glBindVertexArray(VAO);
			
			//generate data VBO
			glGenBuffers(1, &dataVBO[attribIndex]);
			glBindBuffer(GL_ARRAY_BUFFER, dataVBO[attribIndex]);

			//allocate memory for VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfDataPoints, nullptr, GL_DYNAMIC_DRAW);
			
			//vertex attribute pointer
			glEnableVertexAttribArray(attribIndex + 2);
			glVertexAttribDivisor(attribIndex + 2, div);
			glVertexAttribPointer(attribIndex + 2, dataPointsPerInstance, GL_FLOAT, GL_FALSE,
								 sizeof(float) * dataPointsPerInstance, (void*)0);

			numberOfObjectsToRender = numberOfDataPoints / dataPointsPerInstance;
		}

		void VAO_CLASS::writeSubDataVBO_f(int attribIndex, int offset, int numberOfDataPoints, float* VBOdata){
			//bind VAO and VBO
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, dataVBO[attribIndex]);

			//write sub data
			glBufferSubData(GL_ARRAY_BUFFER, (sizeof(float) * offset), 
							sizeof(float) * numberOfDataPoints, VBOdata);

		}

		void VAO_CLASS::allocateDataVBO_i(int attribIndex, int numberOfDataPoints, int dataPointsPerInstance, int div){
			//bind VAO
			glBindVertexArray(VAO);
			
			//generate data VBO
			glGenBuffers(1, &dataVBO[attribIndex]);
			glBindBuffer(GL_ARRAY_BUFFER, dataVBO[attribIndex]);

			//allocate memory for VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLint) * numberOfDataPoints, nullptr, GL_DYNAMIC_DRAW);
			
			//vertex attribute pointer
			glEnableVertexAttribArray(attribIndex + 2);
			glVertexAttribDivisor(attribIndex + 2, div);
			glVertexAttribIPointer(attribIndex + 2, dataPointsPerInstance, GL_INT,
								 sizeof(GLint) * dataPointsPerInstance, (void*)0);

			numberOfObjectsToRender = numberOfDataPoints / dataPointsPerInstance;
		}

		void VAO_CLASS::writeSubDataVBO_i(int attribIndex, int offset, int numberOfDataPoints, GLint* VBOdata){
			//bind VAO and VBO
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, dataVBO[attribIndex]);

			//write sub data
			glBufferSubData(GL_ARRAY_BUFFER, (sizeof(GLint) * offset), 
							sizeof(GLint) * numberOfDataPoints, VBOdata);

		}

		void VAO_CLASS::deleteDataVBO(){
			glBindVertexArray(VAO);
			//unbind any buffers to eliminate risk of deleting currently bound buffer
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			//glDeleteBuffers(1, &dataVBO);
		}

		void VAO_CLASS::render(){
			//bind shader
			shaders::useShader(shaderID);

			//bind VAO
			glBindVertexArray(VAO);

			//issue draw call
		//	std::cout << "draw Call" << std::endl;
			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, numberOfObjectsToRender);
		//	std::cout << "succes" << std::endl;
		}

		GLint* chunkCoords;

		//indices and vertex data for blocks
		unsigned int blockIndexData[6] = {
			0, 1, 2,
			2, 3, 0
		};
		float blockVertexData[4*4] = {
			//  pos    texCoords
			-0.1, -0.1, 0.0, 0.0,
			 0.1, -0.1, 1.0, 0.0,
			 0.1,  0.1, 1.0, 1.0,
		    -0.1,  0.1, 0.0, 1.0
		};
		//indices and vertex data for entities
		unsigned int entityIndexData[6] = {
			0, 1, 2,
			2, 3, 0
		};
		float entityVertexData[4*4] = {
			//  pos    texCoords
			-0.1, -0.1, 0.0, 0.0,
			 0.1, -0.1, 1.0, 0.0,
			 0.1,  0.2, 1.0, 1.0,
		    -0.1,  0.2, 0.0, 1.0
		};

	}
}