#include "Map.h"
#include <iostream>

Map::Map() :
    tileWidth(16), tileHeight(16), tileCols(0), tileRows(0)
{
}

Map::~Map()
{
}

void Map::Initialize()
{
}

void Map::Load()
{
    if (tileSheetTexture.loadFromFile("Assets/World/Prison/tilesheet.png"))
    {
        tileCols = tileSheetTexture.getSize().x / tileWidth;
        tileRows = tileSheetTexture.getSize().y / tileHeight;
        std::cout << "Prison tilesheet texture loaded!" << std::endl;

        int xIndex = 0;
        int yIndex = 2;
        for (int i = 0; i < 10; i++)
        {
            sprites[i].setTexture(tileSheetTexture);
            sprites[i].setTextureRect(sf::IntRect(i * tileWidth, yIndex * tileHeight, tileWidth, tileHeight));
            sprites[i].setScale(5.0f, 5.0f);
            sprites[i].setPosition(sf::Vector2f(100 + i * 5 * tileWidth, 100));
        }

    }
    else
    {
        std::cout << "Prison tilesheet failed to load!" << std::endl;
    }
}

void Map::Update(float deltaTimeMs)
{
}

void Map::Draw(sf::RenderWindow& window)
{
    for (int i = 0; i < 10; i++)
    {
        window.draw(sprites[i]);
    }
}
