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
	spritesheetBanner.loadFromFile("images/PantallaMundo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	banner = Sprite::createSprite(glm::ivec2(256 * 2, 240 * 2), glm::vec2(1, 1), &spritesheetBanner, &shaderProgram);

	text = new Text[3];
	text[0].init(glm::vec2(float(17 * 16), float(10 * 16)), shaderProgram, 2, 0, "0"); //World
	text[1].init(glm::vec2(float(19 * 16), float(10 * 16)), shaderProgram, 2, 0, "0"); //Level
	text[2].init(glm::vec2(float(18 * 16), float(14 * 16)), shaderProgram, 2, 0, "0"); //Vidas

	tileMapDispl = tileMapPos;
	banner->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void PantallaMundo::restart()
{

}

void PantallaMundo::update(int deltaTime, int pos_camara)
{
	banner->setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
	for (int i = 0; i < 3; ++i) text[i].setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
}

void PantallaMundo::render()
{
	banner->render();
	for (int i = 0; i < 3; ++i) text[i].render();
}

void PantallaMundo::setLevel(int world, int level)
{
	text[2].setText(to_string(world));
	text[3].setText(to_string(level));
}

//Quitar
void PantallaMundo::setPoints(int points)
{
	if (points < 10) text[0].setText("000000" + to_string(points));
	else if (points < 100) text[0].setText("00000" + to_string(points));
	else if (points < 1000) text[0].setText("0000" + to_string(points));
	else if (points < 10000) text[0].setText("000" + to_string(points));
	else if (points < 100000) text[0].setText("00" + to_string(points));
	else if (points < 1000000) text[0].setText("0" + to_string(points));
	else text[0].setText(to_string(points));
}

void PantallaMundo::setTime(float gameTime)
{
	int time = 400 - int(gameTime / 1000);
	if (time < 10) text[4].setText("00" + to_string(time));
	else if (time < 100) text[4].setText("0" + to_string(time));
	else text[4].setText(to_string(time));
}
