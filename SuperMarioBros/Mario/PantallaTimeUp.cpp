#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PantallaTimeUp.h"
#include "Game.h"

PantallaTimeUp::~PantallaTimeUp() {

}

void PantallaTimeUp::init(glm::ivec2 tileMapPos, ShaderProgram& shaderProgram)
{
	shader = shaderProgram;
	spritesheetPantallaTimeUp.loadFromFile("images/PantallaTimeUp.png", TEXTURE_PIXEL_FORMAT_RGBA);
	pantallaTimeUp = Sprite::createSprite(glm::ivec2(256 * 2, 240 * 2), glm::vec2(1, 1), &spritesheetPantallaTimeUp, &shaderProgram);

	tileMapDispl = tileMapPos;
	pantallaTimeUp->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void PantallaTimeUp::restart()
{

}

void PantallaTimeUp::update(int deltaTime, int pos_camara)
{
	pantallaTimeUp->setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
}

void PantallaTimeUp::render()
{
	pantallaTimeUp->render();
}