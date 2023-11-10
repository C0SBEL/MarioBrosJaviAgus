#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Credits.h"
#include "Game.h"

Credits::Credits()
{

}

Credits::~Credits()
{

}

void Credits::init() {
	initShaders();
	currentTime = 0.0f;

	spritesheetCredits.loadFromFile("images/PantallaMultiusos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	pantallaCredits = new Sprite();
	pantallaCredits = Sprite::createSprite(glm::ivec2(512, 480), glm::vec2(1.0, 1.0), &spritesheetCredits, &texProgram);

	text = new Text[9]; 
	text[0].init(glm::vec2(float(13 * 16), float(4 * 16)), texProgram, 1, 0, "DEVELOPED BY"); //96
	text[1].init(glm::vec2(float(10 * 16), float(6 * 16)), texProgram, 2, 0, "JAVIER VEGA"); //176
	text[2].init(glm::vec2(float(5 * 16), float(8 * 16)), texProgram, 2, 0, "AND AGUSTI COSTABELLA"); //336

	text[3].init(glm::vec2(float(12 * 16), float(12 * 16)), texProgram, 1, 0, "MAPS DESIGNED BY"); //128
	text[4].init(glm::vec2(float(10 * 16), float(14 * 16)), texProgram, 2, 0, "JAVIER VEGA"); //176
	text[5].init(glm::vec2(float(5 * 16), float(16 * 16)), texProgram, 2, 0, "AND AGUSTI COSTABELLA"); //336

	text[6].init(glm::vec2(float(6 * 16), float(20 * 16)), texProgram, 1, 0, "ORIGINAL TILESHEET AND SPRITESHEETS FROM"); //320
	text[7].init(glm::vec2(float(5 * 16), float(22 * 16)), texProgram, 2, 0, "THE SPRITERS RESOURCE"); //336

	text[8].init(glm::vec2(float(4 * 16), float(25 * 16)), texProgram, 2, 1, "PRESS ESC TO GO TO MENU"); //368

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Credits::update(int deltaTime) {
	currentTime += deltaTime;

	pantallaCredits->update(deltaTime);
	for (int i = 0; i < 9; ++i) text[i].update(deltaTime);
}

void Credits::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	pantallaCredits->render();
	for (int i = 0; i < 9; ++i) text[i].render();
}

void Credits::initShaders()
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