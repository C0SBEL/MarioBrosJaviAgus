#ifndef _PANTALLA_WIN_INCLUDE
#define _PANTALLA_WIN_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include "Text.h"

class PantallaWin
{

public:
	PantallaWin();
	~PantallaWin();

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
	Text* text;
	Texture spritesheetPantallaWin;
	Sprite* pantallaWin;
	bool rPressed, rReleased;
};


#endif 

