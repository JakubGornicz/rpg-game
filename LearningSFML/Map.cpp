#include "Map.h"
#include <iostream>

Map::Map() :
    tilesNumX(0), tilesNumY(0), totalTiles(0), tiles(nullptr), mapSprites(nullptr)
{
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
    mapLoader.Load("Assets/Maps/map.txt", md);
    mapSprites = new sf::Sprite[md.dataSize];

    if (tileSheetTexture.loadFromFile(md.tilesheet))
    {
        tilesNumX = tileSheetTexture.getSize().x / md.tileWidth;
        tilesNumY = tileSheetTexture.getSize().y / md.tileHeight;

		totalTiles = tilesNumX * tilesNumY;

		tiles = new Tile[totalTiles];

        for (size_t y = 0; y < tilesNumY; y++)
        {
            for (size_t x = 0; x < tilesNumX; x++)
            {
				int i = x + y * tilesNumX;

				tiles[i].id = i;
				tiles[i].position = sf::Vector2i(x * md.tileWidth, y * md.tileHeight);
            }
        }
    }
    else
    {
        std::cout << "Prison tilesheet failed to load!" << std::endl;
    }

    for (size_t y = 0; y < md.mapWidth; y++)
    {
        for (size_t x = 0; x < md.mapHeight; x++)
        {
            int i = x + y * md.mapWidth;

            int index = md.data[i];
            mapSprites[i].setTexture(tileSheetTexture);

            mapSprites[i].setTextureRect(sf::IntRect(
                tiles[index].position.x,
                tiles[index].position.y,
                md.tileWidth,
                md.tileHeight));

            mapSprites[i].setScale(sf::Vector2f(md.scaleX, md.scaleY));
            mapSprites[i].setPosition(sf::Vector2f(x * md.tileWidth * md.scaleX,
                                                   y * md.tileHeight * md.scaleY));
        }
    }
}

void Map::Update(float deltaTimeMs)
{
}

void Map::Draw(sf::RenderWindow& window)
{
    for (int i = 0; i < md.dataSize; i++)
    {
        window.draw(mapSprites[i]);
    }
}
