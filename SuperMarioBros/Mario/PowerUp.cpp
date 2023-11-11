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

void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string t)
{
	hit = false;
	activado = true;
	fueraBloque = false;
	movePowerUp = false;
	tipoPowerUp = t;
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
	star = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 1), &spritestar, &shaderProgram);
	star->setNumberAnimations(2);

	star->setAnimationSpeed(HITTED, 8);
	star->addKeyframe(HITTED, glm::vec2(0.2 * 0, 0.f));
	star->addKeyframe(HITTED, glm::vec2(0.2 * 1, 0.f));
	star->addKeyframe(HITTED, glm::vec2(0.2 * 2, 0.f));
	star->addKeyframe(HITTED, glm::vec2(0.2 * 3, 0.f));

	star->setAnimationSpeed(NONE, 8);
	star->addKeyframe(NONE, glm::vec2(0.2 * 4, 0.f));

	mushroom->changeAnimation(NONE);
	star->changeAnimation(NONE);
	mushroom->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(posPowerUp.y + posPowerUp.y)));
	star->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(posPowerUp.y + posPowerUp.y)));
	if (tipoPowerUp == "SETA") sprite = mushroom;
	else sprite = star;
}

void PowerUp::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (!fueraBloque) {
		if (sprite->animation() == NONE && hit)
		{
			sprite->changeAnimation(HITTED);
		}
		else if (sprite->animation() == HITTED && hit)
		{
			if (time >= 30) {
				hit = false;
				fueraBloque = true;
			}
			else {
				++time;
				posPowerUp.y -= 1;
			}
			
			
		}
	}
	else {
		bool colision = map->collisionMoveDown(posPowerUp, glm::vec2(32,32), &posPowerUp.y);
		if (!hit) posPowerUp.y += 4;
		else if (!colision) posPowerUp.y += 1;

		if (movePowerUp)
		{
			posPowerUp.x -= 2;
			if (map->collisionMoveLeft(posPowerUp, glm::vec2(32, 32)))
			{
				movePowerUp = false;
			}
		}
		else
		{
			posPowerUp.x += 2;
			if (map->collisionMoveRight(posPowerUp, glm::vec2(32, 32)))
			{
				movePowerUp = true;
			}
		}
		hit = false;
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPowerUp.x), float(tileMapDispl.y + posPowerUp.y - 4)));
}

void PowerUp::render()
{
	if (activado) sprite->render();
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

bool PowerUp::getFueraBloque() const {
	return fueraBloque;
}

void PowerUp::setHit(string d, const glm::vec2& posB)
{
	time = 0;
	hit = true;

	if (d == "DOWN") {
		int aux = (posPowerUp.y + 32) - posB.y;
		posPowerUp.y -= aux;
	}
}

void PowerUp::setDesactivar() {
	activado = false;
}

string PowerUp::getTipo() {
	return tipoPowerUp;
}