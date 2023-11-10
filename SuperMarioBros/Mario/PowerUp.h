#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class PowerUp
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
	glm::ivec2 tileMapDispl, posPowerUp;
	Texture spritemushroom, spritestar;
	Sprite* mushroom, *sprite, *star;
	TileMap* map;

	int time;
	bool hit, activado;
};

#endif 