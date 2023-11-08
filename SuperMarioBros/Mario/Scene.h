#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Bloque.h" //Tocado
#include "Text.h" //tocado
#include "Banner.h"
#include "Moneda.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void changeLevel(string level);

	bool collisionPlayerEnemy(glm::vec2 pos1, glm::vec2 tam1, glm::vec2 pos2, glm::vec2 tam2);

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	Goomba *goomba;
	Koopa *koopa;
	ShaderProgram texProgram;
	float currentTime;
	float pos_camara;
	glm::mat4 projection;
	
	Bloque* bloque; //tocado
	Text *text; //tocado
	Banner* banner;
	Moneda* moneda;
	int numKoopa, numGoomba, numBloque, numMoneda;
	int numVidasMario, numMonedasMario, puntosMario;
	float gameTime;

};


#endif // _SCENE_INCLUDE

