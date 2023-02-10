#include <iostream>

#include "entities.h"

#include "GameEngine/GameEngine.h"

#include "GameEngine/entity.h"
#include "GameEngine/textures.h"

//textures::TexUnit playerTextures(64, 64, 2);
//textures::Texture playerTex(playerTextures.loadTexture("textures/player.png"));

Player::Player(){
	x = 0;
	y = 0;
	layer = 1.5;

	//textureID = playerTex.index();
}

void Player::tick(){
	GameEngine::Camera::setCamera(x, y);
}