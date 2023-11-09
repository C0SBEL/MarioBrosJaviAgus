#ifndef _PANTALLA_MUNDO
#define _PANTALLA_MUNDO

#include "Sprite.h"
#include "Text.h"


class PantallaMundo
{

public:
	~PantallaMundo();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);
	void restart();

	void update(int deltaTime, int pos_camara);
	void render();
	void setLevel(int world, int level);
	void setPoints(int points);
	void setTime(float gameTime);

private:
	glm::ivec2 tileMapDispl;
	ShaderProgram shader;
	Texture spritesheetBanner;
	Sprite* banner;
	Text* text;
};


#endif // _PANTALLA_MUNDO_INCLUDE
