#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Banner.h"
#include "Game.h"

Banner::~Banner() {

}

void Banner::init(glm::ivec2 tileMapPos, ShaderProgram& shaderProgram)
{
	shader = shaderProgram;
	spritesheetBanner.loadFromFile("images/BannerSuperior.png", TEXTURE_PIXEL_FORMAT_RGBA);
	banner = Sprite::createSprite(glm::ivec2(256*2, 32*2), glm::vec2(1, 1), &spritesheetBanner, &shaderProgram);

	text = new Text[5];
	text[0].init(glm::vec2(float(2 * 16), float(3 * 16)), shaderProgram, 2, "0000000"); //Puntos
	text[1].init(glm::vec2(float(13 * 16), float(3 * 16)), shaderProgram, 2, "00"); //Monedas
	text[2].init(glm::vec2(float(19 * 16), float(3 * 16)), shaderProgram, 2, "0"); //World
	text[3].init(glm::vec2(float(21 * 16), float(3 * 16)), shaderProgram, 2, "0"); //Level
	text[4].init(glm::vec2(float(26 * 16), float(3 * 16)), shaderProgram, 2, "000"); //Tiempo

	tileMapDispl = tileMapPos;
	banner->setPosition(glm::vec2(float(tileMapDispl.x), float(tileMapDispl.y)));
}

void Banner::restart() 
{
	
}

void Banner::update(int deltaTime, int pos_camara)
{
	banner->setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
	for (int i = 0; i < 5; ++i) text[i].setPosition(glm::vec2(float(tileMapDispl.x + pos_camara), float(tileMapDispl.y)));
}

void Banner::render()
{
	banner->render();
	for (int i = 0; i < 5; ++i) text[i].render();
}

void Banner::setLevel(int world, int level) 
{
	string w = to_string(world);
	string l = to_string(level);
	//Hasta aquí funciona
	text[2].setText(w);
	text[3].setText(l);
}

void Banner::setPoints(int points) 
{
	text[0].setText(to_string(points));
}

void Banner::setTime()
{

}


