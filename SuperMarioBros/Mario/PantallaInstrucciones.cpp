#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PantallaInstrucciones.h"
#include "Game.h"

PantallaInstrucciones::PantallaInstrucciones()
{

}

PantallaInstrucciones::~PantallaInstrucciones()
{

}

enum ObjectsAnims
{
	LEFT,RIGHT, DOWN, R, G, M, SPACE, NONE, CHAMPIÑON, ESTRELLA
};

void PantallaInstrucciones::init() {
	initShaders();
	currentTime = 0.0f;

	spritesheetPantallaInstrucciones.loadFromFile("images/PantallaMultiusos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	pantallaInstrucciones = new Sprite();
	pantallaInstrucciones = Sprite::createSprite(glm::ivec2(512, 480), glm::vec2(1.0, 1.0), &spritesheetPantallaInstrucciones, &texProgram);

	//TEXTOS
	text = new Text[7];
	text[0].init(glm::vec2(float(1 * 16), float(8 * 16)), texProgram, 2, 0, "RIGHT ARROW KEY TO MOVE RIGHT");
	text[1].init(glm::vec2(float(2 * 16), float(10 * 16)), texProgram, 2, 0, "LEFT ARROW KEY TO MOVE LEFT"); 
	text[2].init(glm::vec2(float(2 * 16), float(12 * 16)), texProgram, 2, 0, "DOWN ARROW KEY TO GET DOWN"); 

	text[3].init(glm::vec2(float(7 * 16), float(18 * 16)), texProgram, 2, 0, "SPACE BAR TO JUMP"); 
	text[4].init(glm::vec2(float(9 * 16), float(20 * 16)), texProgram, 2, 0, "PRESS R TO RUN"); 

	text[5].init(glm::vec2(float(4 * 16), float(25 * 16)), texProgram, 2, 1, "PRESS ESC TO GO TO MENU");

	text[6].init(glm::vec2(float(9 * 16), float(4 * 16)), texProgram, 2, 1, "-INSTRUCTIONS-");

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void PantallaInstrucciones::update(int deltaTime) {
	currentTime += deltaTime;

	pantallaInstrucciones->update(deltaTime);
	for (int i = 0; i < 7; ++i) text[i].update(deltaTime);
}

void PantallaInstrucciones::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	pantallaInstrucciones->render();
	for (int i = 0; i < 7; ++i) text[i].render();
}

void PantallaInstrucciones::initShaders()
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