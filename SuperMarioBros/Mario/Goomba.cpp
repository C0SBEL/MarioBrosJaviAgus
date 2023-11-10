#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Goomba.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 20
#define JUMP_HEIGHT 20
#define FALL_STEP 2


enum GoombaAnims
{
	MOVE, DEAD, DOWN
};

void Goomba::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Goomba2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE, 8);
	sprite->addKeyframe(MOVE, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(MOVE, glm::vec2(0.25f, 0.f));

	sprite->setAnimationSpeed(DEAD, 8);
	sprite->addKeyframe(DEAD, glm::vec2(0.f, 0.5f));

	sprite->setAnimationSpeed(DOWN, 8);
	sprite->addKeyframe(DOWN, glm::vec2(0.25f, 0.5f));

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
	jumpAngle = 0;
	accelerador = 1;
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
					if (map->collisionMoveLeft(posGoomba, tamGoomba))
					{
						moveGoomba = false;
					}
					if (!map->collisionMoveDown(posGoomba, tamGoomba, &posGoomba.y)) posGoomba.y += 1;
				}
				else
				{
					posGoomba.x += 1;
					if (map->collisionMoveRight(posGoomba, tamGoomba))
					{
						//posGoomba.x -= 0.5;
						moveGoomba = true;
					}
					if (!map->collisionMoveDown(posGoomba, tamGoomba, &posGoomba.y)) posGoomba.y += 1;
				}
			}
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
		}
		else if (dying) {
			if (jumpdie) {
				++time;
				jumpDie();
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posGoomba.x), float(tileMapDispl.y + posGoomba.y)));
				sprite->update(deltaTime);
				if (time == 60) {
					printf("se deja de ver goomba");
					active = false;
					jumpdie = false;
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
}


bool Goomba::isDying() {
	return dying;
}

void Goomba::morintkoopa() {
	sprite->changeAnimation(DOWN);
	dying = true;
	jumpdie = true;
	startY = posGoomba.y;
}

void Goomba::jumpDie() {
	if (jumpdie) {
		if (jumpAngle < 90) {
			jumpAngle += JUMP_ANGLE_STEP;
			posGoomba.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
		}
		else {
			++accelerador;
			posGoomba.y += FALL_STEP + accelerador;
		}
	}
}