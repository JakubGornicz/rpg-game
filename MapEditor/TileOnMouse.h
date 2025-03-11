#pragma once
#include <SFML/Graphics.hpp>
class TileOnMouse
{
private:
	sf::Texture m_tileSheet;
	sf::Sprite m_tile;

	sf::Vector2i m_tileSize;
	sf::Vector2f m_tileScale;

	sf::Vector2f m_position;

public:
	TileOnMouse(const sf::Vector2i& tileSize, const sf::Vector2f& tileScale, const sf::Vector2f& position);
	~TileOnMouse();

	void Initialize();
	void Load();
	void Update(float deltaTimeMs, sf::Vector2f mousePos);
	void Draw(sf::RenderWindow& window);
};

