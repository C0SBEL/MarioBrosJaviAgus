#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PantallaGameOver.h"
#include "Game.h"

PantallaGameOver::PantallaGameOver()
{

}

PantallaGameOver::~PantallaGameOver()
{

}

void PantallaGameOver::init() {
	initShaders();
	currentTime = 0.0f;
	rPressed = false;
	rReleased = false;
	
	spritesheetPantallaMundo.loadFromFile("images/PantallaGameOver.png", TEXTURE_PIXEL_FORMAT_RGBA);
	pantallaGameOver = new Sprite();
	pantallaGameOver = Sprite::createSprite(glm::ivec2(512, 480), glm::vec2(1.0, 1.0), &spritesheetPantallaMundo, &texProgram);

	text = new Text[5];
	text[0].init(glm::vec2(float(2 * 16), float(3 * 16)), texProgram, 2, 0, "0000000"); //Puntos
	text[1].init(glm::vec2(float(13 * 16), float(3 * 16)), texProgram, 2, 0, "00"); //Monedas
	text[2].init(glm::vec2(float(19 * 16), float(3 * 16)), texProgram, 2, 0, "0"); //World
	text[3].init(glm::vec2(float(21 * 16), float(3 * 16)), texProgram, 2, 0, "0"); //Level
	text[4].init(glm::vec2(float(5 * 16), float(23 * 16)), texProgram, 2, 0, "PRESS ESC TO GO TO MENU");

	//pantallaGameOver->setPosition(glm::vec2(float(0), float(0)));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}


void PantallaGameOver::update(int deltaTime) {
	currentTime += deltaTime;

	pantallaGameOver->update(deltaTime);
	for (int i = 0; i < 5; ++i) text[i].update(deltaTime);
}

void PantallaGameOver::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	pantallaGameOver->render();
	for (int i = 0; i < 5; ++i) text[i].render();
}

void PantallaGameOver::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void PantallaGameOver::setPoints(int points)
{
	if (points < 10) text[0].setText("000000" + to_string(points));
	else if (points < 100) text[0].setText("00000" + to_string(points));
	else if (points < 1000) text[0].setText("0000" + to_string(points));
	else if (points < 10000) text[0].setText("000" + to_string(points));
	else if (points < 100000) text[0].setText("00" + to_string(points));
	else if (points < 1000000) text[0].setText("0" + to_string(points));
	else text[0].setText(to_string(points));
}

void PantallaGameOver::setMonedas(int monedas)
{
	if (monedas < 10) text[1].setText("0" + to_string(monedas));
	else text[1].setText(to_string(monedas));
}

void PantallaGameOver::setLevel(int world, int level)
{
	text[2].setText(to_string(world));
	text[3].setText(to_string(level));
}