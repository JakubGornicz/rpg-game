#include "Map.h"
#include "TileOnMouse.h"


Map::Map(const Grid& grid, const TileOnMouse& tileOnMouse) :
	m_mapSprites(nullptr), m_grid(grid), m_tileOnMouse(tileOnMouse)
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
	sf::Vector2i tileGridPosition;
	if (m_tileOnMouse.IsMouseClickedOnTile(tilePosition, tileGridPosition, mousePos))
	{
		int i = tileGridPosition.x + tileGridPosition.y * m_grid.GetTotalCells().x;
		// std::cout << "Tile Position: " << tilePosition.x << " " << tilePosition.y << std::endl;
		// std::cout << "Grid Index: " << i << std::endl;

		m_mapSprites[i] = m_tileOnMouse.GetSprite();
	}
}

void Map::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		window.draw(m_mapSprites[i]);
	}
}