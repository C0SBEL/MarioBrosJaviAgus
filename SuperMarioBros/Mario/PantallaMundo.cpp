#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "PantallaMundo.h"
#include "Game.h"

PantallaMundo::~PantallaMundo() {

}

void PantallaMundo::init(glm::ivec2 tileMapPos, ShaderProgram& shaderProgram)
{
	shader = shaderProgram;
	spritesheetPantallaMundo.loadFromFile("images/PantallaMundo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	pantallaMundo = Sprite::createSprite(glm::ivec2(256 * 2, 240 * 2), glm::vec2(1, 1), &spritesheetPantallaMundo, &shaderProgram);

	text = new Text[3];
	text[0].init(glm::vec2(float(17 * 16), float(10 * 16)), shaderProgram, 2, 0, "0"); //World
	text[1].init(glm::vec2(float(19 * 16), float(10 * 16)), shaderProgram, 2, 0, "0"); //Level
	text[2].init(glm::vec2(float(17 * 16), float(14 * 16)), shaderProgram, 2, 0, "00"); //Vidas

	tileMapDispl = tileMapPos;
	pantallaMundo->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void PantallaMundo::restart()
{

}

void PantallaMundo::update(int deltaTime, int pos_camara)
{
	pantallaMundo->setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
	for (int i = 0; i < 3; ++i) text[i].setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
}

void PantallaMundo::render()
{
	pantallaMundo->render();
	for (int i = 0; i < 3; ++i) text[i].render();
}

void PantallaMundo::setLevel(int world, int level)
{
	text[0].setText(to_string(world));
	text[1].setText(to_string(level));
}

//Quitar
void PantallaMundo::setVides(int vides)
{
	if (vides < 10) text[2].setText("0" + to_string(vides));
	else text[2].setText(to_string(vides));
}

