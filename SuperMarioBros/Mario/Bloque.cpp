#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bloque.h"
#include "Game.h"
#include "Scene.h"


enum BloqueAnims
{
	NOT_HITTED, HITTED, NONE
};

void Bloque::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string t)
{
	hit = false;
	rest = false;
	activado = true;
	tipoBloque = t;
	//INTERROGANTE
	spritesheetInterrogante.loadFromFile("images/BloqueInterrogante.png", TEXTURE_PIXEL_FORMAT_RGBA);
	interrogante = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.2, 1), &spritesheetInterrogante, &shaderProgram);
	interrogante->setNumberAnimations(3);

	interrogante->setAnimationSpeed(NOT_HITTED, 8);
	interrogante->addKeyframe(NOT_HITTED, glm::vec2(0.2 * 0, 0.f));
	interrogante->addKeyframe(NOT_HITTED, glm::vec2(0.2 * 0, 0.f));
	interrogante->addKeyframe(NOT_HITTED, glm::vec2(0.2 * 0, 0.f));
	interrogante->addKeyframe(NOT_HITTED, glm::vec2(0.2 * 1, 0.f));
	interrogante->addKeyframe(NOT_HITTED, glm::vec2(0.2 * 2, 0.f));


	interrogante->setAnimationSpeed(HITTED, 8);
	interrogante->addKeyframe(HITTED, glm::vec2(0.2 * 3, 0.f));

	interrogante->setAnimationSpeed(NONE, 8);
	interrogante->addKeyframe(NONE, glm::vec2(0.2 * 4, 0.f));

	//LADRILLO
	spritesheetLadrillo.loadFromFile("images/BloqueLadrillo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	ladrillo = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheetLadrillo, &shaderProgram);
	ladrillo->setNumberAnimations(3);

	ladrillo->setAnimationSpeed(NOT_HITTED, 8);
	ladrillo->addKeyframe(NOT_HITTED, glm::vec2(0, 0.f));

	ladrillo->setAnimationSpeed(HITTED, 8);
	ladrillo->addKeyframe(HITTED, glm::vec2(0, 0.f));

	ladrillo->setAnimationSpeed(NONE, 8);
	ladrillo->addKeyframe(NONE, glm::vec2(0.5, 0.5f));

	if (t == "INTERROGANTE") 
	{
		interrogante->changeAnimation(NOT_HITTED);
		ladrillo->changeAnimation(NONE);
		tileMapDispl = tileMapPos;
		interrogante->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
		ladrillo->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
		sprite = interrogante;
	}
	else if (t == "LADRILLO")
	{
		interrogante->changeAnimation(HITTED);
		ladrillo->changeAnimation(NOT_HITTED);
		tileMapDispl = tileMapPos;
		interrogante->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
		ladrillo->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));

		sprite = ladrillo;
	}

	
}

void Bloque::update(int deltaTime)
{
	sprite->update(deltaTime);

	if (sprite->animation() == NOT_HITTED && estadoMario == "MARIO")
	{
		if (hit)
		{
			printf(" if hit ");
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y - 10)));
			rest = true;
		}
		if (!hit && rest)
		{
			printf("if hit and rest ");
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
			if (tipoBloque == "INTERROGANTE") sprite->changeAnimation(HITTED);
			hit = false;
			rest = false;
		}
		hit = false;
	}
	if (sprite->animation() == NOT_HITTED && estadoMario == "SUPERMARIO")
	{
		if (hit)
		{
			printf(" if hit ");
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y - 10)));
			rest = true;
		}
		if (!hit && rest)
		{
			printf("if hit and rest ");
			
			if (tipoBloque == "INTERROGANTE") {
				sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
				sprite->changeAnimation(HITTED);
			}
			else {
				sprite->changeAnimation(NONE);
				activado = false;
			}
			hit = false;
			rest = false;
		}
		hit = false;
	}

	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
}

void Bloque::render()
{
	sprite->render();
}

void Bloque::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bloque::setPosition(const glm::vec2& pos)
{
	posBloque = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBloque.x), float(tileMapDispl.y + posBloque.y)));
}


void Bloque::setSprite(string tipoMario)
{
	/*if (tipoMario == "mario") {
		mario->changeAnimation(sprite->animation());
		supermario->changeAnimation(NONE);
		mario->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		sprite = mario;
		tamPlayer = glm::ivec2(32, 32); //Tamaño Mario
	}
	else
	{
		supermario->changeAnimation(sprite->animation());
		mario->changeAnimation(NONE);
		posPlayer.y -= 32; //POSIBLE CAUSA DE ERRORES???
		supermario->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		sprite = supermario;
		tamPlayer = glm::ivec2(32, 64); //Tamaño Super Mario
	}*/
}

glm::vec2 Bloque::getPos() const {

	return posBloque;
}

bool Bloque::getActivo() const {
	return activado;
}

void Bloque::setHit(string eM)
{
	printf(" SET HIT ");
	hit = true;
	estadoMario = eM;
}