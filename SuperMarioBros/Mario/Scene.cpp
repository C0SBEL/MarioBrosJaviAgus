#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 10

#define INIT_GOOMBA_X_TILES 20
#define INIT_GOOMBA_Y_TILES 12

#define INIT_KOOPA_X_TILES 10
#define INIT_KOOPA_Y_TILES 11.5


Scene::Scene()
{
	map = NULL;
	player = NULL;
	goomba = NULL;
	koopa = NULL;
	bloque = NULL;
	banner = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	if(goomba != NULL)
		delete goomba;
	if (koopa != NULL)
		delete koopa;
	if (bloque != NULL)
		delete bloque;
	if (banner != NULL)
		delete banner;
}


void Scene::init()
{
	initShaders();
	changeLevel("level01");
	banner = new Banner();
	banner->init(glm::ivec2(0, 0), texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	currentTime = 0.0f;

	//Tocado
	text = new Text();
	text->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1, "DEVELOPED BY");
	//text->init(glm::vec2(float(2 * 16), float(4 * 16)), texProgram, 2, "0000000"); //Puntos
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	if (goomba != NULL) for (int i = 0; i < numGoomba; ++i) goomba[i].update(deltaTime);
	if (koopa != NULL) for (int i = 0; i < numKoopa; ++i) koopa[i].update(deltaTime);
	player->update(deltaTime, pos_camara);
	banner->update(deltaTime, pos_camara);

	//Tocado 
	glm::vec2 posMario1 = player->getPos();
	glm::vec2 tamM1 = player->getTam();
	if (bloque != NULL)
	{
		glm::vec2 posBloque;
		bool not_collision = true;
		for (int i = 0; i < numBloque && not_collision; ++i)
		{
			posBloque = bloque[i].getPos();
			bool activo = bloque[i].getActivo();
			if (collisionPlayerEnemy(posMario1, tamM1, posBloque, glm::ivec2(32, 32)) && activo) {
				//printf("colision %d ", i);
				if (posMario1.y > posBloque.y) {
					string estadoMario = player->getEstado();
					printf("Bloque");
					bloque[i].setHit(estadoMario);
					player->setBloque("UP", posBloque);
				}
				else if (posMario1.y < posBloque.y + 32) player->setBloque("DOWN", posBloque);
				else if (posMario1.x < posBloque.x) player->setBloque("RIGHT", posBloque);
				else if (posMario1.x > posBloque.x) player->setBloque("LEFT", posBloque);
				not_collision = false;
			}
			else player->setBloque("NONE", posBloque);

			bloque[i].update(deltaTime);
		}
	}
	

	text->update(deltaTime);

	glm::vec2 posMario = player->getPos();
	glm::vec2 tamM = player->getTam();

	//GOOMBA
	if (goomba != NULL)
	{
		for (int i = 0; i < numGoomba; ++i)
		{
			glm::vec2 posGoomba = goomba[i].getPos();
			glm::vec2 tamG = goomba[i].getTam();
			if (!goomba[i].isDying()) {
				if (collisionPlayerEnemy(posMario, tamM, posGoomba, tamG)) {
					if (posMario.y < posGoomba.y) {
						goomba[i].morint();
						player->jump();
					}
					else {
						player->morirsalto();
					}
				}
				//collision goomba con los otros goombas
				for (int j = 0; j < numGoomba; ++j) {
					if (j != i) {
						if (!goomba[j].isDying()) 
					}
				}
			}
		}
	}
	
	//KOOPA
	if (koopa != NULL)
	{
		for (int i = 0; i < numKoopa; ++i)
		{
			glm::vec2 posKoopa = koopa[i].getPos();
			glm::vec2 tamK = koopa[i].getTam();
			if (collisionPlayerEnemy(posMario, tamM, posKoopa, tamK)) {
				if (posMario.y + tamM.y / 2 <= posKoopa.y) {
					player->jump();
					if (koopa[i].isShell()) {
						bool left = posKoopa.x < posMario.x;
						koopa[i].moveShell(left);
					}
					else {
						koopa[i].transformToShell();
					}
				}
				else {
					player->morirsalto();
				}
			}
		}
	}

	if (player->isRebooted()) {
		changeLevel("level01");
	}
	

	
	//collision goombas koopas
	/*
	*  if (!goomba->isDying() && collisionPlayerEnemy(posGoomba, tamG, posKoopa, tamK)) {
		printf("colision koopa goomba!!!");
		if (koopa->isShell()) {
			goomba->morintkoopa();
		}
		else {
			goomba->changeDirection();
			koopa->changeDirection();
		}
	}
	*/
	//collision goombas


	//collision koopas



	//SCROLL
	float cuadrant = posMario.x - pos_camara;
	if (cuadrant >= SCREEN_WIDTH / 3) {
		pos_camara += player->getVel();
		projection = glm::ortho(pos_camara, float(SCREEN_WIDTH) + pos_camara, float(SCREEN_HEIGHT), 0.f);
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	if (goomba != NULL) for (int i = 0; i < numGoomba; ++i) goomba[i].render();
	if (koopa != NULL) for (int i = 0; i < numKoopa; ++i) koopa[i].render();
	//Tocado
	if (bloque != NULL) for (int i = 0; i < numBloque; ++i) bloque[i].render();
	text->render(); 
	banner->render();
}

void Scene::changeLevel(string level)
{
	//Elimino los elementos anteriores
	goomba = NULL;
	koopa = NULL;
	bloque = NULL;
	numKoopa = 0;
	numGoomba = 0;
	numBloque = 0;
	printf("changelevel");

	//Cambio de nivel
	if (level == "level01") {
		map = TileMap::createTileMap("levels/level01.txt", "levels/objects01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
		player = new Player();
		player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		player->setTileMap(map);

		//banner->setLevel(1, 1);

		vector<pair<int, int>> posGoombas = map->getPosObj("GOOMBAS");
		numGoomba = posGoombas.size();
		printf(" Numero goombas: %d", numGoomba);
		if (numGoomba > 0)
		{
			goomba = new Goomba[numGoomba];
			for (int i = 0; i < numGoomba; ++i)
			{
				goomba[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				goomba[i].setPosition(glm::vec2(posGoombas[i].first * map->getTileSize(), posGoombas[i].second * map->getTileSize()));
				goomba[i].setTileMap(map);
			}
		}
		
		vector<pair<int, int>> posKoopas = map->getPosObj("KOOPAS");
		numKoopa = posKoopas.size();
		printf(" Numero koopas: %d", numKoopa);
		if (numKoopa > 0)
		{
			koopa = new Koopa[numKoopa];
			for (int i = 0; i < numKoopa; ++i)
			{
				koopa[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				koopa[i].setPosition(glm::vec2((posKoopas[i].first+0.5f) * map->getTileSize(), (posKoopas[i].second + 0.5f) * map->getTileSize()));
				koopa[i].setTileMap(map);
			}
		}
		
		vector<pair<int, int>> posInterrogantes = map->getPosObj("INTERROGANTES");
		vector<pair<int, int>> posLadrillos = map->getPosObj("LADRILLOS");
		int numI = posInterrogantes.size();
		int numL = posLadrillos.size();
		numBloque = numI + numL;
		if (numBloque > 0)
		{
			bloque = new Bloque[numBloque];
			int i = 0;
			for (int j = 0; j < numI; ++j)
			{
				bloque[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "INTERROGANTE");
				bloque[i].setPosition(glm::vec2(posInterrogantes[j].first * map->getTileSize(), posInterrogantes[j].second * map->getTileSize()));
				bloque[i].setTileMap(map);
				++i;
			}
			for (int j = 0; j < numL; ++j)
			{
				bloque[i].init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "LADRILLO");
				bloque[i].setPosition(glm::vec2(posLadrillos[j].first * map->getTileSize(), posLadrillos[j].second * map->getTileSize()));
				bloque[i].setTileMap(map);
				++i;
			}
		}

		pos_camara = 0;
	}
}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::collisionPlayerEnemy(glm::vec2 pos1, glm::vec2 tam1, glm::vec2 pos2, glm::vec2 tam2)
{
	float minx1 = pos1.x;
	float miny1 = pos1.y;
	float maxx1 = pos1.x + tam1.x;
	float maxy1 = pos1.y + tam1.y;
	float minx2 = pos2.x;
	float miny2 = pos2.y;
	float maxx2 = pos2.x + tam2.x;
	float maxy2 = pos2.y + tam2.y;
	if ((minx1 < maxx2) && (minx2 < maxx1) && (miny1 < maxy2) && (miny2 < maxy1)) return true;
	return false;
}

