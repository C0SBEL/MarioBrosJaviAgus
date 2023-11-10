#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum CurrentScreen {
	PANTALLA_INICIAL, GAME, GAME_OVER, WIN, CREDITS
};

void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	currentScreen = PANTALLA_INICIAL;
	pantallaInicial.init();
	scene.init();
	pantallaGameOver.init();
	credits.init();
}

bool Game::update(int deltaTime)
{
	switch (currentScreen)
	{
	case PANTALLA_INICIAL:
		pantallaInicial.update(deltaTime);
		break;
	case GAME:
		scene.update(deltaTime);
		if (scene.isGameOver()) {
			int points = scene.getPoints();
			int monedas = scene.getMonedas();
			int world = scene.getWorld();
			int level = scene.getLevel();
			currentScreen = GAME_OVER;
			pantallaGameOver.setPoints(points);
			pantallaGameOver.setMonedas(monedas);
			pantallaGameOver.setLevel(world, level);

			int record = scene.getRecord();
			pantallaInicial.setPoints(record);
		}
		if (scene.hasWon()) {
			/*int points = scene.getPoints();
			int monedas = scene.getMonedas();
			int world = scene.getWorld();
			int level = scene.getLevel();
			
			pantallaWin.setPoints(points);
			pantallaWin.setMonedas(monedas);
			pantallaWin.setLevel(world, level);*/

			//currentScreen = WIN;

			/*int record = scene.getRecord();
			pantallaInicial.setPoints(record);*/
		}
		break;
	case GAME_OVER:
		pantallaGameOver.update(deltaTime);
		break;
	case WIN:
		pantallaWin.update(deltaTime);
		break;
	case CREDITS:
		credits.update(deltaTime);
		break;
	}
	
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (currentScreen)
	{
	case PANTALLA_INICIAL:
		pantallaInicial.render();
		break;
	case GAME:
		scene.render();
		break;
	case GAME_OVER:
		pantallaGameOver.render();
		break;
	case WIN:
		pantallaWin.render();
		break;
	case CREDITS:
		credits.render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) {// Escape code
		switch (currentScreen) 
		{
		case PANTALLA_INICIAL:
			bPlay = false;
			break;
		case GAME:
			break;
		case GAME_OVER:
			currentScreen = PANTALLA_INICIAL;
			break;
		case WIN:
			currentScreen = PANTALLA_INICIAL;
			break;
		case CREDITS:
			currentScreen = PANTALLA_INICIAL;
			break;
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button, int x, int y)
{
	if (currentScreen == PANTALLA_INICIAL) {
		if (x >= 112 && x < 176 && y >= 240 && y < 256) {
			currentScreen = GAME;
			scene.restart();
		}
		if (x >= 240 && x < 432 && y >= 240 && y < 256) {
			//currentScreen = INSTRUCTIONS;
		}
		if (x >= 80 && x < 192 && y >= 288 && y < 316) {
			currentScreen = CREDITS;
		}
		if (x >= 304 && x < 368 && y >= 288 && y < 316) {
			bPlay = false;
		}
	}
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





