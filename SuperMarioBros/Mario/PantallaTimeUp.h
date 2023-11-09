#ifndef _PANTALLA_TIME_UP
#define _PANTALLA_TIME_UP

#include "Sprite.h"
#include "Text.h"


class PantallaTimeUp
{

public:
	~PantallaTimeUp();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);
	void restart();

	void update(int deltaTime, int pos_camara);
	void render();
	void setLevel(int world, int level);
	void setVides(int vides);

private:
	glm::ivec2 tileMapDispl;
	ShaderProgram shader;
	Texture spritesheetPantallaTimeUp;
	Sprite* pantallaTimeUp;
};

#endif // _PANTALLA_MUNDO_INCLUDE
