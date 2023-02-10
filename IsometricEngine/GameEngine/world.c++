#include <iostream>
#include <thread>

#include "world.h"

#include <cstdlib>

#include "GameEngine.h"
#include "entity.h"
#include "renderer.h"

class GrassBlock : public entity::block{
public:
	void tick(){}
	GrassBlock(){
		textureID = 1.0;
	}
private:
};

class UglyBlock : public entity::block{
public:
	void tick(){}
	UglyBlock(){
		textureID = 2.0;
	}
private:
};

class AirBlock : public entity::block{
public:
	void tick(){}
	AirBlock(){
		textureID = 0.0;
	}
private:
};

class testEntity : public entity::entity{
public:
	void tick(){}
	testEntity(float i_x, float i_y){
		textureID = 1.0;

		x = i_x;
		y = i_y;
		layer = 1.1;
	}
private:
};




namespace world {
	/*
	generata new world
	*/
	void newWorld(){
		worldData = new Chunk[RENDER_DIST * RENDER_DIST];
	}


	void loadWorld(){
		worldData = new Chunk[RENDER_DIST * RENDER_DIST];

		srand(15);

		for(int i = 0; i < RENDER_DIST * RENDER_DIST; i++){
			//set chunk data
			worldData[i].chunkX = getChunkX(i);
			worldData[i].chunkY = getChunkY(i);

			//generate blocks
			for(int u = 0; u < CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT; u++){
				if(u < CHUNK_WIDTH * CHUNK_WIDTH){

					worldData[i].blocks[u] = GrassBlock();
				}else if(u % 16 == 0){
					worldData[i].blocks[u] = UglyBlock();
				}else{
					worldData[i].blocks[u] = AirBlock();
				}
			}


			//generate entities
			for(int u = 0; u < MAX_NUMBER_OF_ENTITIES_PER_CHUNK / 2; u++){
				worldData[i].entities[u] = testEntity(rand() % 16, rand() % 16);
			}

		}

	}

	void unloadWorld(){
		delete[] worldData;
	}



	void updateChunks(){
		//loop through all chunks
		for(int chunkX = 0; chunkX < RENDER_DIST; chunkX++){
			for(int chunkY = 0; chunkY < RENDER_DIST; chunkY++){
				
				int chunkIndex = (chunkY * RENDER_DIST) + chunkX;

				//update entities
				player -> tick();
				for(int i = 0; i < MAX_NUMBER_OF_ENTITIES_PER_CHUNK; i++){
					worldData[chunkIndex].entityDrawData[(i * DATA_POINTS_PER_ENTITY) + 0] = 
						worldData[chunkIndex].entities[i].x + static_cast<float>(chunkX * CHUNK_WIDTH);

					worldData[chunkIndex].entityDrawData[(i * DATA_POINTS_PER_ENTITY) + 1] = 
						worldData[chunkIndex].entities[i].y + static_cast<float>(chunkY * CHUNK_WIDTH); 
					//std::cout << worldData[chunkIndex].entities[(i * 4) + 1].y + static_cast<float>(chunkY) << std::endl;
					worldData[chunkIndex].entityDrawData[(i * DATA_POINTS_PER_ENTITY) + 2] = 
						worldData[chunkIndex].entities[i].layer; 

					worldData[chunkIndex].entityDrawData[(i * DATA_POINTS_PER_ENTITY) + 3] = 
						worldData[chunkIndex].entities[i].textureID;
				}

				renderer::VAO::writeEntityData(chunkX, chunkY, &worldData[chunkIndex].entityDrawData[0]);

				//update blocks
				for(int y = 0; y < WORLD_HEIGHT; y++){
					for(int x = 0; x < CHUNK_WIDTH; x++){
						for(int z = 0; z < CHUNK_WIDTH; z++){

							
							int blockIndex = (CHUNK_WIDTH * CHUNK_WIDTH * y) + (CHUNK_WIDTH * x) + z;
							
							worldData[chunkIndex].blockDrawData[(blockIndex * DATA_POINTS_PER_BLOCK) + 0] =
								worldData[chunkIndex].blocks[blockIndex].textureID;
						}
					}
				}

				renderer::VAO::writeBlockData(chunkX, chunkY, &worldData[chunkIndex].blockDrawData[0]);
			}		
		}
	}


	entity::block* getBlock(int x, int y){
		return &worldData[getChunkIndex(x / RENDER_DIST, y / RENDER_DIST)].
				blocks[getBlockIndex(x % CHUNK_WIDTH, y % CHUNK_WIDTH)];
	}

	void setBlock(int x, int y, entity::block newBlock){
		worldData[getChunkIndex(x / RENDER_DIST, y / RENDER_DIST)].
				blocks[getBlockIndex(x % CHUNK_WIDTH, y % CHUNK_WIDTH)] = newBlock;	
	}

	entity::player* getPlayer(){
		return player;
	}

	void setPlayer(entity::player* newPlayer){
		player = newPlayer;
	}

	
	namespace {
		Chunk* worldData;

		int getBlockIndex(int x, int y){
			return (y * CHUNK_WIDTH) + x;
		}

		int getChunkIndex(int x, int y){
			return (y * RENDER_DIST) + x;
		}

		int getChunkX(int index){
			return index / RENDER_DIST;
		}

		int getChunkY(int index){
			return index % RENDER_DIST;
		}

		int getBlockX(int index){
			return index / CHUNK_WIDTH;
		}

		int getBlockY(int index){
			return index % CHUNK_WIDTH;
		}

		Chunk::Chunk(){
			blocks = new entity::block[CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT];
			blockDrawData = new float[CHUNK_WIDTH * CHUNK_WIDTH * WORLD_HEIGHT * DATA_POINTS_PER_BLOCK];

			entities = new entity::entity[MAX_NUMBER_OF_ENTITIES_PER_CHUNK];
			entityDrawData = new float[MAX_NUMBER_OF_ENTITIES_PER_CHUNK * DATA_POINTS_PER_ENTITY];
		}

		Chunk::~Chunk(){

			delete[] blocks;
			delete[] blockDrawData;

			delete[] entities;
			delete[] entityDrawData;
		}


	}

}