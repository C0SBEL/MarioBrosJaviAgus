#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime,float poscam);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setSprite(string tipoMario);

	glm::vec2 getPos() const;
	glm::vec2 getTam() const;
	int getVel() const;
	string getEstado() const;
	void setBloque(string direction, const glm::vec2 &posB);
	void jump();
	void morirsalto();
	bool isActive();
	bool isDying();
	bool isRebooted();
	bool isFalling();
	void cambiaEstado(string estadoanterior, string estadoposterior);
	bool esInmune();
	bool isWin();
	void setWin();
	
	
private:
	bool bJumping, dying, active, rebooted, falling, superMario, starMario, inmunidad, renderizar, mastil, win, finivel;
	glm::ivec2 tileMapDispl, posPlayer, tamPlayer, posBloque;
	int jumpAngle, startY, vel, jump_angle_step, jump_height, fall_step;
	Texture spritesheetMario, spritesheetSuperMario;
	Sprite *sprite, *mario, *supermario;
	TileMap *map;
	string hitBloque;
	int time, timeinm, aux, timeBandera;


};


#endif // _PLAYER_INCLUDE


