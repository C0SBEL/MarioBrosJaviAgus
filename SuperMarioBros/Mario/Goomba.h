#ifndef _GOOMBA_INCLUDE
#define _GOOMBA_INCLUDE

#include "Sprite.h"
#include "TileMap.h"



// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Goomba
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void morir();
	glm::vec2 getPos() const;
	glm::vec2 getTam() const;
	bool isDying();

	void morint();
	void changeDirection();
	void morintkoopa();
	void jumpDie();



private:
	bool moveGoomba, active, dying, dead, jumpdie;
	glm::ivec2 tileMapDispl, posGoomba, tamGoomba;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
	int time, ini, velocidadY;

};


#endif // _GOOMBA_INCLUDE