#include "Map.h"
#include <iostream>

Map::Map() :
    tileWidth(16), tileHeight(16), tilesNumX(0), tilesNumY(0), totalTiles(0),
	mapWidth(3), mapHeight(3), tiles(nullptr)
{
    tiles = nullptr; // Initialize tiles to nullptr
}

Map::~Map()
{
    delete[] tiles; // Clean up allocated memory
}

void Map::Initialize()
{
}

void Map::Load()
{
    if (tileSheetTexture.loadFromFile("Assets/World/Prison/tilesheet.png"))
    {
        tilesNumX = tileSheetTexture.getSize().x / tileWidth;
        tilesNumY = tileSheetTexture.getSize().y / tileHeight;

		totalTiles = tilesNumX * tilesNumY;

		tiles = new Tile[totalTiles];

        for (size_t y = 0; y < tilesNumY; y++)
        {
            for (size_t x = 0; x < tilesNumX; x++)
            {
				int i = x + y * tilesNumX;

				tiles[i].id = i;
				tiles[i].position = sf::Vector2i(x * tileWidth, y * tileHeight);
            }
        }
    }
    else
    {
        std::cout << "Prison tilesheet failed to load!" << std::endl;
    }

    for (size_t y = 0; y < mapHeight; y++)
    {
        for (size_t x = 0; x < mapWidth; x++)
        {
            int i = x + y * mapWidth;

            int index = mapIndexes[i];
            mapSprites[i].setTexture(tileSheetTexture);

            mapSprites[i].setTextureRect(sf::IntRect(
                tiles[index].position.x,
                tiles[index].position.y,
                tileWidth,
                tileHeight));

            mapSprites[i].setScale(sf::Vector2f(5, 5));
            mapSprites[i].setPosition(sf::Vector2f(x * tileWidth * mapSprites[i].getScale().x , 
                                                   y * tileHeight * mapSprites[i].getScale().y));
        }
    }
}

void Map::Update(float deltaTimeMs)
{
}

void Map::Draw(sf::RenderWindow& window)
{
    for (int i = 0; i < mapSize; i++)
    {
        window.draw(mapSprites[i]);
    }
}
