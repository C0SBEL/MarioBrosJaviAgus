#include "PowerUp.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Scene.h"

enum PowerUpAnims
{
	HITTED, NONE
};

void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	hit = false;
	activado = true;
	tileMapDispl = tileMapPos;

	//mushroom

	spritemushroom.loadFromFile("images/mushroom.png", TEXTURE_PIXEL_FORMAT_RGBA);
	mushroom = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 1), &spritemushroom, &shaderProgram);
	mushroom->setNumberAnimations(2);

	mushroom->setAnimationSpeed(HITTED, 8);
	mushroom->addKeyframe(HITTED, glm::vec2(0, 0.f));

	mushroom->setAnimationSpeed(NONE, 8);
	mushroom->addKeyframe(NONE, glm::vec2(0.5, 0.f));

	//star

	spritestar.loadFromFile("images/star.png", TEXTURE_PIXEL_FORMAT_RGBA);
	star = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 1), &spritemushroom, &shaderProgram);
	star ->setNumberAnimations(2);

	star ->setAnimationSpeed(HITTED, 8);
	star ->addKeyframe(HITTED, glm::vec2(0, 0.f));

	star ->setAnimationSpeed(NONE, 8);
	star->addKeyframe(NONE, glm::vec2(0.5, 0.f));

	mushroom->changeAnimation(NONE);
	star->changeAnimation(HITTED);
	mushroom->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(posPowerUp.y + posPowerUp.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(posPowerUp.y + posPowerUp.y)));
	sprite = mushroom;
}

void PowerUp::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (sprite->animation() == NONE && hit)
	{
		sprite->changeAnimation(HITTED);
		//posPowerUp.y -= 32;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(tileMapDispl.y + posPowerUp.y)));
	}
	else if (sprite->animation() == HITTED && hit)
	{
		if (time >= 32) hit = false;
		else ++time;

		posPowerUp.y -= 1;
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(tileMapDispl.y + posPowerUp.y)));
	}
	/*else if (sprite->animation() == HITTED && !hit)
	{
		sprite->changeAnimation(NONE);
	}*/
}

void PowerUp::render()
{
	sprite->render();
}

void PowerUp::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void PowerUp::setPosition(const glm::vec2& pos)
{
	posPowerUp = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(tileMapDispl.y + posPowerUp.y)));
}

glm::vec2 PowerUp::getPos() const {

	return posPowerUp;
}

bool PowerUp::getActivo() const {
	return activado;
}

void PowerUp::setHit()
{
	time = 0;
	hit = true;
	activado = false;
}