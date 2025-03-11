#include "TileOnMouse.h"
#include <iostream>

TileOnMouse::TileOnMouse(
	const sf::Vector2i& tileSize,
	const sf::Vector2f& tileScale,
	const sf::Vector2f& position) :
	m_tileSize(tileSize), m_tileScale(tileScale), m_position(position)
{
}

TileOnMouse::~TileOnMouse()
{
}

void TileOnMouse::Initialize()
{
}

void TileOnMouse::Load()
{
	if (m_tileSheet.loadFromFile("Assets/World/Prison/tilesheet.png"))
	{
		std::cout << "Tilesheet texture loaded succesfully!" << std::endl;
		m_tile.setTexture(m_tileSheet);
		m_tile.setTextureRect(sf::IntRect(3 * m_tileSize.x, 0 * m_tileSize.y, m_tileSize.x, m_tileSize.y));
		m_tile.setScale(m_tileScale);
	}
	else
	{
		std::cout << "TileOnMouse Load: Tilesheet failed to load!" << std::endl;
	}
}

void TileOnMouse::Update(float deltaTimeMs, sf::Vector2f mousePos)
{
	// casting to int to determine in which cell the mouse is 
	int x = (int) mousePos.x / (m_tileSize.x * m_tileScale.x);
	int y = (int) mousePos.y / (m_tileSize.y * m_tileScale.y);

	// setting the position of the tile to the cell pointed by the mouse
	m_tile.setPosition(sf::Vector2f(
						   x * m_tileSize.x * m_tileScale.x,
						   y * m_tileSize.y * m_tileScale.y
	));
}

void TileOnMouse::Draw(sf::RenderWindow& window)
{
	window.draw(m_tile);
}
