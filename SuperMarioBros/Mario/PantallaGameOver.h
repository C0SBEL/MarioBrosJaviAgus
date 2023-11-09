#ifndef _PANTALLA_GAME_OVER_INCLUDE
#define _PANTALLA_GAME_OVER_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Text.h"

class PantallaGameOver
{

public:
	PantallaGameOver();
	~PantallaGameOver();

	void init();
	void update(int deltaTime);
	void render();

	void setPoints(int points);
	void setMonedas(int monedas);
	void setLevel(int world, int level);

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	glm::mat4 projection;
	float currentTime;
	Text * text;
	Texture spritesheetPantallaMundo;
	Sprite* pantallaGameOver;
	bool rPressed, rReleased;
};


#endif 
