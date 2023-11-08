#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "Scene.h"12

#include "Text.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 128
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, BEND_LEFT, BEND_RIGHT, TURN_LEFT, TURN_RIGHT, NONE, DEAD
};

enum CambioEstadoAnims
{
	MARIO_SUPERMARIO_LEFT, MARIO_SUPERMARIO_RIGHT, SUPERMARIO_MARIO_LEFT, SUPERMARIO_MARIO_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	dying = false;
	vel = 5;
	time = 0;
	active = true;
	rebooted = false;

	//MARIO
	double tamM = 0.125;
	spritesheetMario.loadFromFile("images/Mario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	mario = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(tamM, 0.5), &spritesheetMario, &shaderProgram);
	mario->setNumberAnimations(12);

	mario->setAnimationSpeed(STAND_LEFT, 8);
	mario->addKeyframe(STAND_LEFT, glm::vec2(tamM*0, 0.5f));

	mario->setAnimationSpeed(STAND_RIGHT, 8);
	mario->addKeyframe(STAND_RIGHT, glm::vec2(tamM*0, 0.f));

	mario->setAnimationSpeed(MOVE_LEFT, 8);
	mario->addKeyframe(MOVE_LEFT, glm::vec2(tamM*1, 0.5f));
	mario->addKeyframe(MOVE_LEFT, glm::vec2(tamM*2, 0.5f));
	mario->addKeyframe(MOVE_LEFT, glm::vec2(tamM*3, 0.5f));

	mario->setAnimationSpeed(MOVE_RIGHT, 8);
	mario->addKeyframe(MOVE_RIGHT, glm::vec2(tamM*1, 0.f));
	mario->addKeyframe(MOVE_RIGHT, glm::vec2(tamM*2, 0.f));
	mario->addKeyframe(MOVE_RIGHT, glm::vec2(tamM*3, 0.f));

	mario->setAnimationSpeed(JUMP_LEFT, 8);
	mario->addKeyframe(JUMP_LEFT, glm::vec2(tamM*5, 0.5f));

	mario->setAnimationSpeed(JUMP_RIGHT, 8);
	mario->addKeyframe(JUMP_RIGHT, glm::vec2(tamM*5, 0.f));

	mario->setAnimationSpeed(BEND_LEFT, 8);
	mario->addKeyframe(BEND_LEFT, glm::vec2(tamM*0, 0.5f));

	mario->setAnimationSpeed(BEND_RIGHT, 8);
	mario->addKeyframe(BEND_RIGHT, glm::vec2(tamM*0, 0.f));

	mario->setAnimationSpeed(TURN_LEFT, 8);
	mario->addKeyframe(TURN_LEFT, glm::vec2(tamM * 4, 0.5f));

	mario->setAnimationSpeed(TURN_RIGHT, 8);
	mario->addKeyframe(TURN_RIGHT, glm::vec2(tamM * 4, 0.f));

	mario->setAnimationSpeed(NONE, 8);
	mario->addKeyframe(NONE, glm::vec2(tamM*7, 0.f));

	mario->setAnimationSpeed(DEAD, 8);
	mario->addKeyframe(DEAD, glm::vec2(tamM*6, 0.f));


	//SUPER MARIO
	double tamSM = 0.125;
	spritesheetSuperMario.loadFromFile("images/SuperMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	supermario = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(tamSM, 0.5), &spritesheetSuperMario, &shaderProgram);
	supermario->setNumberAnimations(11);

	supermario->setAnimationSpeed(STAND_LEFT, 8);
	supermario->addKeyframe(STAND_LEFT, glm::vec2(tamSM*0, 0.5f));

	supermario->setAnimationSpeed(STAND_RIGHT, 8);
	supermario->addKeyframe(STAND_RIGHT, glm::vec2(tamSM*0, 0.f));

	supermario->setAnimationSpeed(MOVE_LEFT, 8);
	supermario->addKeyframe(MOVE_LEFT, glm::vec2(tamSM*1, 0.5f));
	supermario->addKeyframe(MOVE_LEFT, glm::vec2(tamSM*2, 0.5f));
	supermario->addKeyframe(MOVE_LEFT, glm::vec2(tamSM*3, 0.5f));

	supermario->setAnimationSpeed(MOVE_RIGHT, 8);
	supermario->addKeyframe(MOVE_RIGHT, glm::vec2(tamSM*1, 0.f));
	supermario->addKeyframe(MOVE_RIGHT, glm::vec2(tamSM*2, 0.f));
	supermario->addKeyframe(MOVE_RIGHT, glm::vec2(tamSM*3, 0.f));

	supermario->setAnimationSpeed(JUMP_LEFT, 8);
	supermario->addKeyframe(JUMP_LEFT, glm::vec2(tamSM*5, 0.5f));

	supermario->setAnimationSpeed(JUMP_RIGHT, 8);
	supermario->addKeyframe(JUMP_RIGHT, glm::vec2(tamSM*5, 0.f));

	supermario->setAnimationSpeed(BEND_LEFT, 8);
	supermario->addKeyframe(BEND_LEFT, glm::vec2(tamSM*6, 0.5f));

	supermario->setAnimationSpeed(BEND_RIGHT, 8);
	supermario->addKeyframe(BEND_RIGHT, glm::vec2(tamSM*6, 0.f));

	supermario->setAnimationSpeed(TURN_LEFT, 8);
	supermario->addKeyframe(TURN_LEFT, glm::vec2(tamSM * 4, 0.5f));

	supermario->setAnimationSpeed(TURN_RIGHT, 8);
	supermario->addKeyframe(TURN_RIGHT, glm::vec2(tamSM * 4, 0.f));

	supermario->setAnimationSpeed(NONE, 8);
	supermario->addKeyframe(NONE, glm::vec2(tamSM*7, 0.f));

	//Animación cambio estado
	double tamAnim = 0.125;
	spritesheetCambioEstado.loadFromFile("images/Animacion1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cambioestado = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(tamAnim, 0.5), &spritesheetCambioEstado, &shaderProgram);
	cambioestado->setNumberAnimations(2);

	cambioestado->setAnimationSpeed(MARIO_SUPERMARIO_LEFT, 8);
	cambioestado->addKeyframe(MARIO_SUPERMARIO_LEFT, glm::vec2(tamAnim * 0, 0.5f));
	cambioestado->addKeyframe(MARIO_SUPERMARIO_LEFT, glm::vec2(tamAnim * 1, 0.5f));
	cambioestado->addKeyframe(MARIO_SUPERMARIO_LEFT, glm::vec2(tamAnim * 2, 0.5f));

	cambioestado->setAnimationSpeed(MARIO_SUPERMARIO_RIGHT, 8);
	cambioestado->addKeyframe(MARIO_SUPERMARIO_RIGHT, glm::vec2(tamAnim * 0, 0.f));
	cambioestado->addKeyframe(MARIO_SUPERMARIO_RIGHT, glm::vec2(tamAnim * 1, 0.f));
	cambioestado->addKeyframe(MARIO_SUPERMARIO_RIGHT, glm::vec2(tamAnim * 2, 0.f));

	cambioestado->setAnimationSpeed(SUPERMARIO_MARIO_LEFT, 8);
	cambioestado->addKeyframe(SUPERMARIO_MARIO_LEFT, glm::vec2(tamAnim * 3, 0.5f));
	cambioestado->addKeyframe(SUPERMARIO_MARIO_LEFT, glm::vec2(tamAnim * 4, 0.5f));
	cambioestado->addKeyframe(SUPERMARIO_MARIO_LEFT, glm::vec2(tamAnim * 5, 0.5f));
	cambioestado->addKeyframe(SUPERMARIO_MARIO_LEFT, glm::vec2(tamAnim * 6, 0.5f));

	cambioestado->setAnimationSpeed(SUPERMARIO_MARIO_RIGHT, 8);
	cambioestado->addKeyframe(SUPERMARIO_MARIO_RIGHT, glm::vec2(tamAnim * 3, 0.f));
	cambioestado->addKeyframe(SUPERMARIO_MARIO_RIGHT, glm::vec2(tamAnim * 4, 0.f));
	cambioestado->addKeyframe(SUPERMARIO_MARIO_RIGHT, glm::vec2(tamAnim * 5, 0.f));
	cambioestado->addKeyframe(SUPERMARIO_MARIO_RIGHT, glm::vec2(tamAnim * 6, 0.f));

	cambioestado->setAnimationSpeed(NONE, 8);
	cambioestado->addKeyframe(NONE, glm::vec2(tamAnim * 7, 0.f));

	mario->changeAnimation(0);
	supermario->changeAnimation(NONE);
	cambioestado->changeAnimation(NONE);
	tileMapDispl = tileMapPos;
	mario->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	supermario->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
	sprite = mario;
	tamPlayer = glm::ivec2(32, 32); //Tamaño Mario

}

void Player::update(int deltaTime, float poscam)
{
	if (active) {
		sprite->update(deltaTime);
		printf("Pos Player y: %d \n", posPlayer.y);
		//se va del mapa
		if (posPlayer.y > 14 * tamPlayer.x) {
			posPlayer.y = 14 * tamPlayer.x;
			dying = true;
			sprite->changeAnimation(DEAD);
		}

		//Animación aterrizaje salto (JUMP_X --> STAND_X)
		if (!bJumping && sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
		if (!bJumping && sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);

		//Cambio manual de estado (Mario <--> Super Mario)
		if (Game::instance().getKey('m') || Game::instance().getKey('M'))
		{
			if (sprite != mario) setSprite("mario");
			else setSprite("supermario");

			Game::instance().keyReleased('M');
			Game::instance().keyReleased('m');
		}

		//Control aceleración
		if (Game::instance().getKey('r') || Game::instance().getKey('R'))
		{
			//if (vel == 2) vel = 5;
			vel = 4;
		}
		//else if ((!Game::instance().getSpecialKey(GLUT_KEY_LEFT) || !Game::instance().getSpecialKey(GLUT_KEY_RIGHT) && !Game::instance().getSpecialKey(GLUT_KEY_DOWN))) vel = 2;
		else vel = 2;

		if (!dying) {
			if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
			{
				if (bJumping) sprite->changeAnimation(JUMP_LEFT);
				else if (sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);

				if (posPlayer.x > poscam - float(vel)) posPlayer.x -= vel;
				//else posPlayer.x = poscam;

				if (map->collisionMoveLeft(posPlayer, tamPlayer) || hitBloque == "LEFT")
				{
					posPlayer.x += vel;
					sprite->changeAnimation(STAND_LEFT);
					//printf("Colision Left");
				}
			}
			//Tecla derecha
			else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
			{
				if (bJumping) sprite->changeAnimation(JUMP_RIGHT);
				else if (sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);

				posPlayer.x += vel;

				if (map->collisionMoveRight(posPlayer, tamPlayer) || hitBloque == "RIGHT")
				{
					posPlayer.x -= vel;
					sprite->changeAnimation(STAND_RIGHT);
				}
			}
			//Tecla abajo
			else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
			{
				if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(BEND_LEFT);
				else if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(BEND_RIGHT);
			}
			else
			{
				if (sprite->animation() == MOVE_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == MOVE_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
				else if (sprite->animation() == BEND_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() == BEND_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
			}

		}

		//Salto con tecla arriba (KEY_UP --> bJumping; no KEY_UP --> !bJumping)
		if (bJumping)
		{
			//Animación salto (STAND_X --> JUMP_X)
			if (!dying) {
				if (sprite->animation() == STAND_LEFT) sprite->changeAnimation(JUMP_LEFT);
				if (sprite->animation() == STAND_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
			}
			else {
				sprite->changeAnimation(DEAD);
			}

			jumpAngle += JUMP_ANGLE_STEP;
			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{
				posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
				if (jumpAngle > 90) {
					bJumping = !map->collisionMoveDown(posPlayer, tamPlayer, &posPlayer.y);
					if (hitBloque == "DOWN")
					{
						bJumping = false;
					}
				}
				else {
					//jumpAngle = 180 - jumpAngle;
					bJumping = !map->collisionMoveUp(posPlayer, tamPlayer);
					if (hitBloque == "UP") {
						bJumping = false;
					}
				}
			}
		}
		else
		{
			posPlayer.y += FALL_STEP;
			if (map->collisionMoveDown(posPlayer, tamPlayer, &posPlayer.y) || hitBloque == "DOWN")
			{
				//Activa el salto
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			}
		}

		if (dying) {
			time++;
			if (time == 40) {
				rebooted = true;
			}

		}
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	}
}

void Player::render()
{
	if (active) sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}


void Player::setSprite(string tipoMario)
{
	if (tipoMario == "mario") {
		mario->changeAnimation(sprite->animation());
		supermario->changeAnimation(NONE);
		mario->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		sprite = mario;
		tamPlayer = glm::ivec2(32, 32); //Tamaño Mario
	}
	else
	{
		supermario->changeAnimation(sprite->animation());
		mario->changeAnimation(NONE);
		posPlayer.y -= 32; //POSIBLE CAUSA DE ERRORES???
		supermario->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
		sprite = supermario;
		tamPlayer = glm::ivec2(32, 64); //Tamaño Super Mario
	}
}

glm::vec2 Player::getPos() const{

	return posPlayer;
}

int Player::getVel() const {

	return vel;
}

glm::vec2 Player::getTam() const {

	return tamPlayer;
}

string Player::getEstado() const
{
	if (sprite == mario) return "MARIO";
	else if (sprite == supermario) return "SUPERMARIO";
}

void Player::setBloque(string d, const glm::vec2 &posB) 
{
	hitBloque = d;
	posBloque = posB;
	/*if (hitBloque == "UP") printf(" UP ");
	else if (hitBloque == "DOWN") printf(" DOWN ");
	else if (hitBloque == "LEFT") printf(" LEFT ");
	else if (hitBloque == "RIGHT") printf(" RIGHT ");
	else if (hitBloque == "NONE") printf(" NONE ");*/
	if (hitBloque == "DOWN")
	{
		int aux = (posPlayer.y + tamPlayer.y) - posB.y;
		posPlayer.y -= aux;
	}
}

void Player::jump() {	
	jumpAngle = 0;
	startY = posPlayer.y;
	bJumping = true;
}

void Player::morirsalto() {
	dying = true;
	jump();
	sprite->changeAnimation(DEAD);
}

bool Player::isActive() {
	return active;
}

bool Player::isDying() {
	return dying;
}

bool Player::isRebooted() {
	return rebooted;
}