#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const string& objectFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, objectFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string &levelFile, const string& objectFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
	cargarElementos(objectFile);
}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	string mapline, tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	for (int j = 0; j<mapSize.y; j++)
	{
		getline(fin, line);
		stringstream mapline(line);
		for (int i = 0; i<mapSize.x; i++)
		{
			mapline >> tile;
			int n = stoi(tile);
			map[j * mapSize.x + i] = n;
		}
#ifndef _WIN32
		fin.get(tile);
#endif
	}

	fin.close();
	/*posGoombas = {{15, 12}, {25, 12}};
	posKoopas = { { 20, 12 }, { 6, 12 } };
	posInterrogantes = { {16,11}, {22,10}, {21,9}, {75, 9}, {91,5}, {104,9}, {107, 5} };*/
	return true;
}

bool TileMap::cargarElementos(const string& objectFile) {
	ifstream fin;
	string line;
	stringstream sstream;

	fin.open(objectFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 6, "GOOMBA") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	int numG;
	sstream >> numG;
	posGoombas = vector<pair<int, int>>(numG);

	sstream.clear();  // Clear the error state of the stringstream
	sstream.seekg(0); // Reset the stream position to the beginning of the line

	getline(fin, line);
	sstream.str(line);
	for (int i = 0; i < numG; ++i) {
		pair<int, int> aux;
		sstream >> aux.first >> aux.second;
		posGoombas[i] = aux;
	}

	sstream.clear();
	sstream.seekg(0);

	//Posiciones Koopas
	getline(fin, line);
	if (line.compare(0, 5, "KOOPA") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	int numK;
	sstream >> numK;
	posKoopas = vector<pair<int, int>>(numK);

	sstream.clear();
	sstream.seekg(0);

	getline(fin, line);
	sstream.str(line);
	for (int i = 0; i < numK; ++i) {
		pair<int, int> aux;
		sstream >> aux.first >> aux.second;
		posKoopas[i] = aux;
	}

	sstream.clear();
	sstream.seekg(0);

	//Posiciones Bloque ?
	getline(fin, line);
	if (line.compare(0, 12, "INTERROGANTE") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	int numI;
	sstream >> numI;
	posInterrogantes = vector<pair<int, int>>(numI);

	sstream.clear();
	sstream.seekg(0);

	getline(fin, line);
	sstream.str(line);
	for (int i = 0; i < numI; ++i) {
		pair<int, int> aux;
		sstream >> aux.first >> aux.second;
		posInterrogantes[i] = aux;
	}

	sstream.clear();
	sstream.seekg(0);

	//Posiciones Bloque Ladrillo
	getline(fin, line);
	if (line.compare(0, 8, "LADRILLO") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	int numL;
	sstream >> numL;
	posLadrillos = vector<pair<int, int>>(numL);

	sstream.clear();
	sstream.seekg(0);

	getline(fin, line);
	sstream.str(line);
	for (int i = 0; i < numL; ++i) {
		pair<int, int> aux;
		sstream >> aux.first >> aux.second;
		posLadrillos[i] = aux;
	}

	sstream.clear();
	sstream.seekg(0);

	//Posiciones Monedas
	getline(fin, line);
	if (line.compare(0, 8, "MONEDA") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	int numM;
	sstream >> numM;
	posMonedas = vector<pair<int, int>>(numM);

	sstream.clear();
	sstream.seekg(0);

	getline(fin, line);
	sstream.str(line);
	for (int i = 0; i < numM; ++i) {
		pair<int, int> aux;
		sstream >> aux.first >> aux.second;
		posMonedas[i] = aux;
	}

	sstream.clear();
	sstream.seekg(0);

	//Posiciones Monedas
	getline(fin, line);
	if (line.compare(0, 8, "SETA") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	int numS;
	sstream >> numS;
	posSetas = vector<pair<int, int>>(numS);

	sstream.clear();
	sstream.seekg(0);

	getline(fin, line);
	sstream.str(line);
	for (int i = 0; i < numS; ++i) {
		pair<int, int> aux;
		sstream >> aux.first >> aux.second;
		posSetas[i] = aux;
	}

	fin.close();

	return true;
}

vector<pair<int, int>> TileMap::getPosObj(string n)
{
	if (n == "GOOMBAS") return posGoombas;
	else if (n == "KOOPAS") return posKoopas;
	else if (n == "INTERROGANTES") return posInterrogantes;
	else if (n == "LADRILLOS") return posLadrillos;
	else if (n == "MONEDAS") return posMonedas;
	else if (n == "SETAS") return posSetas;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(1e-5f, 1e-5f);
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		return isCollision(map[y * mapSize.x + x]);
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		return isCollision(map[y * mapSize.x + x]);
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (isCollision(map[y * mapSize.x + x]))
			if (*posY - tileSize * y + size.y <= 30)
			{
				//printf("colision abajo");
				*posY = tileSize * y - size.y;
				return true;
			}
	}

	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (isCollision(map[y * mapSize.x + x]))
		{
			return true;
		}
	}

	return false;
}

bool TileMap::isCollision(const int n) const
{
	//return n != 4 && n != 17 && n != 18 && n != 19 && n != 25 && n != 26 && n != 27 && n != 9 && n != 10 && n != 11;
	return n == 1 || n == 2 || n == 3 || n == 42 || n == 44 || n == 45 || n == 52 || n == 53 || n == 57 || n == 58 || n == 59;
}

bool TileMap::collisionMastil(const glm::ivec2& pos, const glm::ivec2& size) const {

	int mastil[] = {43, 51};
	int x, y;

	x = (pos.x + size.x / 2 + 4) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;

	return (map[y * mapSize.x + x] == 43 || map[y * mapSize.x + x] == 51);
}