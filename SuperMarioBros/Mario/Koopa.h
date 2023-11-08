#ifndef _KOOPA_INCLUDE
#define _KOOPA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Koopa
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void transformToShell() ;
	void changeDirection();
	glm::vec2 getPos() const;
	glm::vec2 getTam() const;
	bool isShell();
	void moveShell(bool left);

private:
	bool moveKoopa, moveshell = false, left;
	glm::ivec2 tileMapDispl, posKoopa;
	glm::vec2 tamKoopa;
	int jumpAngle, startY;
	Texture spritesheet, spritesheetshell;
	Sprite* sprite, *spritekoopa, *spriteshell;
	TileMap* map;
	int vel;

};


#endif // _KOOPA_INCLUDE