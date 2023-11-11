#ifndef _POWERUP_INCLUDE
#define _POWERUP_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class PowerUp
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string tipoPowerUp);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);

	glm::vec2 getPos() const;
	bool getActivo() const;
	bool getFueraBloque() const;
	void setHit(string d, const glm::vec2& posB);
	void setDesactivar();
	string getTipo();


private:
	glm::ivec2 tileMapDispl, posPowerUp;
	Texture spritemushroom, spritestar;
	Sprite* mushroom, *sprite, *star;
	TileMap* map;

	int time, movePowerUp;
	bool hit, activado, fueraBloque;
	string tipoPowerUp;
};

#endif 