#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
private:
	sf::Texture tileSheetTexture;

	Tile* tiles;

	int tilesNumX;
	int tilesNumY;
	int totalTiles;

	int tileWidth;
	int tileHeight;

	static const int mapSize = 9;
	int mapWidth;
	int mapHeight;

	int mapIndexes[mapSize] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8
	};

	sf::Sprite mapSprites[mapSize];

	
public:
	Map();
	~Map();
	void Initialize();
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);
};