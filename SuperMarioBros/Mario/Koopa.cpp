#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Koopa.h"
#include "Game.h"

enum KoopaAnims
{
	MOVE_LEFT, MOVE_RIGHT, SHELL, SHELL_LEGS, NONE
};

void Koopa::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile("images/Koopa.png", TEXTURE_PIXEL_FORMAT_RGBA);
	float tamk = 0.5;
	spritekoopa = Sprite::createSprite(glm::ivec2(32, 48), glm::vec2(tamk, 0.5), &spritesheet, &shaderProgram);
	spritekoopa->setNumberAnimations(3);

	spritekoopa->setAnimationSpeed(MOVE_LEFT, 8);
	spritekoopa->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
	spritekoopa->addKeyframe(MOVE_LEFT, glm::vec2(tamk, 0.f));

	spritekoopa->setAnimationSpeed(MOVE_RIGHT, 8);
	spritekoopa->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.5f));
	spritekoopa->addKeyframe(MOVE_RIGHT, glm::vec2(tamk, 0.5f));

	spritekoopa->setAnimationSpeed(NONE, 8);
	spritekoopa->addKeyframe(NONE, glm::vec2(2*tamk, 0.f));

	spritesheetshell.loadFromFile("images/KoopaCaparazon.png", TEXTURE_PIXEL_FORMAT_RGBA);
	float tams = 0.5;
	spriteshell = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(tams, 1.f), &spritesheetshell, &shaderProgram);

	spriteshell->setNumberAnimations(3);

	spriteshell->setAnimationSpeed(SHELL, 8);
	spriteshell->addKeyframe(SHELL, glm::vec2(0.f, 0.f));

	spriteshell->setAnimationSpeed(SHELL_LEGS, 8);
	spriteshell->addKeyframe(SHELL_LEGS, glm::vec2(tams, 0.f));

	spriteshell->setAnimationSpeed(NONE, 8);
	spriteshell->addKeyframe(NONE, glm::vec2(2*tams, 0.f));

	spritekoopa->changeAnimation(MOVE_LEFT);
	spriteshell->changeAnimation(NONE);
	tileMapDispl = tileMapPos;
	spritekoopa->setPosition(glm::vec2(float(tileMapDispl.x + posKoopa.x), float(tileMapDispl.y + posKoopa.y)));
	spriteshell->setPosition(glm::vec2(float(tileMapDispl.x + posKoopa.x), float(tileMapDispl.y + posKoopa.y)));
	tamKoopa = glm::vec2(32, 48);
	sprite = spritekoopa;
	vel = 1;
	//tam shell = (32,32)

}

void Koopa::update(int deltaTime)
{
	sprite->update(deltaTime);
	//printf("Pos Koopa y: %d \n", posKoopa.y);
	if (sprite == spritekoopa){
		if (sprite->animation() == MOVE_LEFT){
			posKoopa.x -= vel;
				if (map->collisionMoveLeft(posKoopa, tamKoopa) || posKoopa.x <= 0) sprite->changeAnimation(MOVE_RIGHT);
		}
		else if (sprite->animation() == MOVE_RIGHT){
			posKoopa.x += vel;
			if (map->collisionMoveRight(posKoopa, tamKoopa) || posKoopa.x >= 240 ) sprite->changeAnimation(MOVE_LEFT);
		}
	}

	else if (moveshell) {
		if (left)
		{
			posKoopa.x -= vel;
			if (map->collisionMoveLeft(posKoopa, tamKoopa) || posKoopa.x <= 0)
			{
				left = false;
			}
		}
		else
		{
			posKoopa.x += vel;
			if (map->collisionMoveRight(posKoopa, tamKoopa) || posKoopa.x >= 240 * 32)
			{
				left = true;
			}
		}

	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posKoopa.x), float(tileMapDispl.y + posKoopa.y)));
}

void Koopa::render()
{
	sprite->render();
}

void Koopa::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Koopa::setPosition(const glm::vec2& pos)
{
	posKoopa = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posKoopa.x), float(tileMapDispl.y + posKoopa.y)));
}

glm::vec2 Koopa::getPos() const {

	return posKoopa;
}

glm::vec2 Koopa::getTam() const {

	return tamKoopa;
}

void Koopa::transformToShell() {
	spriteshell->changeAnimation(NONE);
	spritekoopa->changeAnimation(NONE);
	spriteshell->setPosition(glm::vec2(float(tileMapDispl.x + posKoopa.x), float(tileMapDispl.y + posKoopa.y)));
	tamKoopa = glm::vec2(32, 30);
	sprite = spriteshell;
	posKoopa.y += 20; //esto tendria que ser +16 pero el que no tiene piernas esta un pixel arriba
}

void Koopa::changeDirection() {
	if ((sprite->animation() == MOVE_LEFT)) sprite->changeAnimation(MOVE_RIGHT);
	else sprite->changeAnimation(MOVE_LEFT);
}

void Koopa::moveShell(bool left) {
	vel = 4;
	moveshell = true;
	this->left = left;
}

bool Koopa::isShell() {
	return sprite == spriteshell;
}

bool Koopa::ismoveShell() {
	return moveshell;
}
