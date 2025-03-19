#include "TileOnMouse.h"
#include <iostream>
#include <stdlib.h>


TileOnMouse::TileOnMouse(
	const sf::Vector2i& tileSize,
	const sf::Vector2f& tileScale,
	const sf::Vector2f& offset) :
	m_tileSize(tileSize), m_tileScale(tileScale), m_offset(offset), m_isMouseOnGrid(false), nextTileX(0), nextTileY(0)
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

void TileOnMouse::Update(float deltaTimeMs, const sf::Vector2f& mousePos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_tile.setTextureRect(sf::IntRect(0 * m_tileSize.x, 3 * m_tileSize.y, m_tileSize.x, m_tileSize.y));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_tile.setTextureRect(sf::IntRect(1 * m_tileSize.x, 3 * m_tileSize.y, m_tileSize.x, m_tileSize.y));
	}

	// casting to int to determine in which cell the mouse is 
	m_tileGridPosition.x = static_cast<int>((mousePos.x - m_offset.x) / (m_tileSize.x * m_tileScale.x));
	m_tileGridPosition.y = static_cast<int>((mousePos.y - m_offset.y) / (m_tileSize.y * m_tileScale.y));
	
	m_tilePosition.x = m_tileGridPosition.x * m_tileSize.x * m_tileScale.x + m_offset.x;
	m_tilePosition.y = m_tileGridPosition.y * m_tileSize.y * m_tileScale.y + m_offset.y;
	
	// setting the position of the tile to the cell pointed by the mouse
	m_tile.setPosition(sf::Vector2f(m_tilePosition));
}

void TileOnMouse::Draw(sf::RenderWindow& window)
{
	window.draw(m_tile);
}

bool TileOnMouse::IsMouseClickedOnTile(
	sf::Vector2f& tilePosition,
	sf::Vector2i& tileGridPosition,
	const sf::Vector2f& mousePos) const
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{	
		// setting the position of the tile to the cell pointed by the mouse
		tilePosition = m_tilePosition;
		tileGridPosition = m_tileGridPosition;
		return true;
	}
	return false;
}
