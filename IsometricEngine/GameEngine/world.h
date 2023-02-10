#pragma once

#include "entity.h"


#define CHUNK_WIDTH 16

#define MAX_NUMBER_OF_ENTITIES_PER_CHUNK 64

#define DATA_POINTS_PER_BLOCK 1
#define DATA_POINTS_PER_ENTITY 4

namespace world {

	void newWorld();
	void loadWorld();
	void unloadWorld();

	void updateChunks();

	entity::block* getBlock(int x, int y);
	void setBlock(int x, int y, entity::block newBlock);

	entity::player* getPlayer();
	void setPlayer(entity::player* newPlayer);


	namespace {

		int getBlockIndex(int x, int y);
		int getChunkIndex(int x, int y);
		int getChunkX(int index);
		int getChunkY(int index);
		int getBlockX(int index);
		int getBlockY(int index);


		class Chunk{
		public:
			Chunk();
			~Chunk();


			entity::block* blocks;
			float* blockDrawData;

			entity::entity* entities;
			float* entityDrawData;
			int numberOfEntities;

			int chunkX;
			int chunkY;
		private:
		};

		entity::player* player;

		extern Chunk* worldData;
	}
}

