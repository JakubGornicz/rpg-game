#include "Map.h"
#include "TileOnMouse.h"


Map::Map(TileOnMouse& tileOnMouse) :
	m_mapSprites(nullptr), m_tileOnMouse(tileOnMouse)
{

}

Map::~Map()
{
	delete[] m_mapSprites;
}

void Map::Initialize()
{
	m_mapSprites = new sf::Sprite[MAP_SIZE];
}

void Map::Load()
{

}

void Map::Update(float deltaTimeMs, const sf::Vector2f& mousePos)
{
	sf::Vector2f tilePosition;
	if (m_tileOnMouse.IsMouseClickedOnTile(tilePosition, mousePos))
	{
		std::cout << "Tile Position: " << tilePosition.x << " " << tilePosition.y << std::endl;
	}
}

void Map::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		window.draw(m_mapSprites[i]);
	}
}