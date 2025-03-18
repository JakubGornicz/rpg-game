#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TileOnMouse.h"

#define MAP_SIZE 50

class Map
{
private:
	TileOnMouse& m_tileOnMouse;
	sf::Sprite* m_mapSprites;
public:
	Map(TileOnMouse& tileOnMouse);
	~Map();

	void Initialize();
	void Load();
	void Update(float deltaTimeMs, const sf::Vector2f& mousePos);
	void Draw(sf::RenderWindow& window);
};

