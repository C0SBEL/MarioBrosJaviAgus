#ifndef _TEXT_INCLUDE
#define _TEXT_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Text
{
public:
	~Text();
	void init(const glm::ivec2& pos, ShaderProgram& shaderProgram, int size, string text);
	void update(int deltaTime);
	void render();

	void initSprites(int size);
	void setPosition(const glm::vec2& pos);
	void setText(string newText);

private:
	glm::ivec2 posText;
	Texture spritesheet;
	Sprite* sprite;
	ShaderProgram shader;
	int size, sizeText;

};


#endif // _TEXT_INCLUDE
