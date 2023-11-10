#ifndef _MONEDA_INCLUDE
#define _MONEDA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Moneda
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	glm::vec2 getPos() const;
	bool getActivo() const;
	void setHit();


private:
	glm::ivec2 tileMapDispl, posMoneda;
	Texture spritesheetMoneda;
	Sprite* moneda;
	TileMap* map;

	int time;
	bool hit, activado;
};

#endif 