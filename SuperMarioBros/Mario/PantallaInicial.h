#ifndef _PANTALLA_INICIAL_INCLUDE
#define _PANTALLA_INICIAL_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"
#include "Sprite.h"

class PantallaInicial
{

public:
	PantallaInicial();
	~PantallaInicial();

	void init();
	void update(int deltaTime);
	void render();

	void setPoints(int points);

private:
	void initShaders();


private:
	ShaderProgram texProgram;
	Texture spritesheetPantallaInicial;
	Sprite* pantallaInicial;
	glm::mat4 projection;
	float currentTime;
	Text* text;
};


#endif 
