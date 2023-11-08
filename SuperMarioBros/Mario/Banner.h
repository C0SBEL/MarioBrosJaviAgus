#ifndef _BANNER_INCLUDE
#define _BANNER_INCLUDE

#include "Sprite.h"
#include "Text.h"


class Banner
{

public:
	~Banner();
	void init(glm::ivec2 pos, ShaderProgram& shaderProgram);
	void restart();

	void update(int deltaTime, int pos_camara);
	void render();
	void setLevel(int world, int level);
	void setPoints(int points);
	void setTime();

private:
	glm::ivec2 tileMapDispl;
	ShaderProgram shader;
	Texture spritesheetBanner;
	Sprite* banner;
	Text* text;
};


#endif // _BANNER_INCLUDE

