#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Text.h"
#include "Sprite.h"

class Credits
{

public:
	Credits();
	~Credits();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();


private:
	ShaderProgram texProgram;
	Texture spritesheetCredits;
	Sprite* pantallaCredits;
	glm::mat4 projection;
	float currentTime;
	Text* text;
};


#endif 
