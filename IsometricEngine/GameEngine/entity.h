#pragma once

/*
Collision variables for each entity
*/


namespace entity {
	class block {
	public:
		void tick(); //virtuaö
		int blockID;
		float textureID;
	private:
	};

	class entity {
	public:
		virtual void tick();

		float textureID;
		float x;
		float y;
		float layer;
	private:

	};

	class player : public entity{
	public:
		void tick() = 0;

	private:


	};
}