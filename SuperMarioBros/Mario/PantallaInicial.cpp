#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PantallaInicial.h"
#include "Game.h"

PantallaInicial::PantallaInicial()
{

}

PantallaInicial::~PantallaInicial()
{

}

void PantallaInicial::init() {
	initShaders();
	currentTime = 0.0f;
	
	spritesheetPantallaInicial.loadFromFile("images/PantallaInicial.png", TEXTURE_PIXEL_FORMAT_RGBA);
	pantallaInicial = new Sprite();
	pantallaInicial = Sprite::createSprite(glm::ivec2(512, 480), glm::vec2(1.0, 1.0), &spritesheetPantallaInicial, &texProgram);

	text = new Text[5];
	text[0].init(glm::vec2(float(7 * 16), float(15 * 16)), texProgram, 2, 0, "PLAY");
	text[1].init(glm::vec2(float(15 * 16), float(15 * 16)), texProgram, 2, 0, "INSTRUCTIONS");
	text[2].init(glm::vec2(float(5 * 16), float(18 * 16)), texProgram, 2, 0, "CREDITS");
	text[3].init(glm::vec2(float(19* 16), float(18 * 16)), texProgram, 2, 0, "EXIT");
	text[4].init(glm::vec2(float(16 * 16), float(23 * 16)), texProgram, 2, 0, "0000000"); //Puntos

	//pantallaInicial->setPosition(glm::vec2(float(0), float(0)));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void PantallaInicial::update(int deltaTime) {
	currentTime += deltaTime;

	pantallaInicial->update(deltaTime);
	for (int i = 0; i < 5; ++i) text[i].update(deltaTime);
}

void PantallaInicial::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	pantallaInicial->render();
	for (int i = 0; i < 5; ++i) text[i].render();
}

void PantallaInicial::initShaders()
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

void PantallaInicial::setPoints(int points)
{
	if (points < 10) text[4].setText("000000" + to_string(points));
	else if (points < 100) text[4].setText("00000" + to_string(points));
	else if (points < 1000) text[4].setText("0000" + to_string(points));
	else if (points < 10000) text[4].setText("000" + to_string(points));
	else if (points < 100000) text[4].setText("00" + to_string(points));
	else if (points < 1000000) text[4].setText("0" + to_string(points));
	else text[4].setText(to_string(points));
}