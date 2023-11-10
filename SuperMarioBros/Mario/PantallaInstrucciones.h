#ifndef _PANTALLA_INSTRUCCIONES_INCLUDE
#define _PANTALLA_INSTRUCCIONES_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"
#include "Sprite.h"

class PantallaInstrucciones
{

public:
	PantallaInstrucciones();
	~PantallaInstrucciones();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();


private:
	ShaderProgram texProgram;
	Texture spritesheetPantallaInstrucciones;
	Sprite* pantallaInstrucciones;
	glm::mat4 projection;
	float currentTime;
	Text* text;
};


#endif
