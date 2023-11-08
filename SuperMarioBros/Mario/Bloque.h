#ifndef _BLOQUE_INCLUDE
#define _BLOQUE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Bloque
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, string tipo);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setSprite(string tipoMario);

	glm::vec2 getPos() const;
	bool getActivo() const;
	void setHit(string estadoMario);


private:
	glm::ivec2 tileMapDispl, posBloque;
	Texture spritesheetInterrogante, spritesheetLadrillo;
	Sprite* sprite, * interrogante, * ladrillo;
	TileMap* map;

	
	bool hit, rest, activado;
	string estadoMario, tipoBloque;
};

#endif 
