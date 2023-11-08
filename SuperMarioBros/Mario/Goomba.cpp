#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Goomba.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 128
#define FALL_STEP 8


enum GoombaAnims
{
	MOVE, DEAD
};

void Goomba::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Goomba2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVE, 8);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE, glm::vec2(0.5f, 0.f));

	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(MOVE);
	moveGoomba = true;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y))); 
	tamGoomba = glm::vec2(32, 32);
	active = true;
	dying = false;
	dead = false;
	jumpdie = false;
	ini = 2;
	time = 0;
}

void Goomba::update(int deltaTime)
{
	if (active) {
		if (!dying) {
			sprite->update(deltaTime);
			if (sprite->animation() == MOVE) {
				if (moveGoomba)
				{
					posGoomba.x -= 1;
					if (map->collisionMoveLeft(posGoomba, tamGoomba) || posGoomba.x <= 0)
					{
						moveGoomba = false;
					}
				}
				else
				{
					posGoomba.x += 1;
					if (map->collisionMoveRight(posGoomba, tamGoomba) || posGoomba.x >= 240 * 32)
					{
						//posGoomba.x -= 0.5;
						moveGoomba = true;
					}
				}
			}
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
		}
		else if (dying) {
			if (jumpdie) {
				++time;
				jumpDie();
				sprite->update(deltaTime);
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
				if (time == 60) {
					active = false;
					time = 0;
				}
			}
			else {
				++time;
				if (time == 30) {
					active = false;
					time = 0;
				}
			}
		}
	}
}

void Goomba::render()
{
	if (active) sprite->render();
}

void Goomba::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Goomba::setPosition(const glm::vec2& pos)
{
	posGoomba = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
}

glm::vec2 Goomba::getPos() const {

	return posGoomba;
}

glm::vec2 Goomba::getTam() const {

	return tamGoomba;
}

void Goomba::morint() {
	sprite->changeAnimation(DEAD);
	dying = true;
}


void Goomba::changeDirection() {
	moveGoomba = !moveGoomba;
	printf(" cambio direcci�n goomba ");
}


bool Goomba::isDying() {
	return dying;
}

void Goomba::morintkoopa() {
	dying = true;
	jumpdie = true;
	startY = posGoomba.y;
}

void Goomba::jumpDie() {
	if (jumpdie) {
		jumpAngle += JUMP_ANGLE_STEP;

	    posGoomba.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
	}
	else posGoomba.y += FALL_STEP;
}