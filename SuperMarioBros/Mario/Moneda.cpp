#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Moneda.h"
#include "Game.h"
#include "Scene.h"


enum BloqueAnims
{
	HITTED, NONE
};

void Moneda::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	hit = false;
	activado = true;

	spritesheetMoneda.loadFromFile("images/Moneda.png", TEXTURE_PIXEL_FORMAT_RGBA);
	moneda = Sprite::createSprite(glm::ivec2(16, 32), glm::vec2(0.2, 1), &spritesheetMoneda, &shaderProgram);
	moneda->setNumberAnimations(2);

	moneda->setAnimationSpeed(HITTED, 8);
	moneda->addKeyframe(HITTED, glm::vec2(0.2 * 0, 0.f));
	moneda->addKeyframe(HITTED, glm::vec2(0.2 * 1, 0.f));
	moneda->addKeyframe(HITTED, glm::vec2(0.2 * 2, 0.f));
	moneda->addKeyframe(HITTED, glm::vec2(0.2 * 3, 0.f));

	moneda->setAnimationSpeed(NONE, 8);
	moneda->addKeyframe(NONE, glm::vec2(0.2 * 4, 0.f));
	
	moneda->changeAnimation(HITTED);
	tileMapDispl = tileMapPos;
	moneda->setPosition(glm::vec2(float(tileMapDispl.x + posMoneda.x), float(tileMapDispl.y + posMoneda.y)));
}

void Moneda::update(int deltaTime)
{
	moneda->update(deltaTime);

	/*if (moneda->animation() == NONE)
	{
		if (hit)
		{
			moneda->changeAnimation(HITTED);
			moneda->setPosition(glm::vec2(float(tileMapDispl.x + posMoneda.x), float(tileMapDispl.y + posMoneda.y - 64)));
			hit = false;
		}
	}
	else if (moneda->animation() == HITTED) 
	{
		if (!hit)
		{
			moneda->changeAnimation(NONE);
			moneda->setPosition(glm::vec2(float(tileMapDispl.x + posMoneda.x), float(tileMapDispl.y + posMoneda.y + 64)));
			activado = false;
		}
	}*/
	moneda->setPosition(glm::vec2(float(tileMapDispl.x + posMoneda.x), float(tileMapDispl.y + posMoneda.y)));
}

void Moneda::render()
{
	moneda->render();
}

void Moneda::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Moneda::setPosition(const glm::vec2& pos)
{
	posMoneda = pos;
	moneda->setPosition(glm::vec2(float(tileMapDispl.x + posMoneda.x), float(tileMapDispl.y + posMoneda.y)));
}

glm::vec2 Moneda::getPos() const {

	return posMoneda;
}

bool Moneda::getActivo() const {
	return activado;
}

void Moneda::setHit()
{
	printf(" SET HIT ");
	hit = true;
}