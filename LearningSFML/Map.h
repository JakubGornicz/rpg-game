#pragma once
#include <SFML/Graphics.hpp>
class Map
{
private:
	sf::Texture tileSheetTexture;
	sf::Sprite sprites[10];
	int tileWidth;
	int tileHeight;

	int tileRows;
	int tileCols;
public:
	Map();
	~Map();
	void Initialize();
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);
};

