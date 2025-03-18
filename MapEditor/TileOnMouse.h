#pragma once
#include <SFML/Graphics.hpp>

class TileOnMouse
{
private:
	sf::Texture m_tileSheet;
	sf::Sprite m_tile;

	sf::Vector2f m_tilePosition;
	sf::Vector2i m_tileGridPosition;

	sf::Vector2i m_tileSize;
	sf::Vector2f m_tileScale;
	sf::Vector2f m_offset;

	bool m_isMouseOnGrid;

public:
	TileOnMouse(const sf::Vector2i& tileSize, const sf::Vector2f& tileScale, const sf::Vector2f& offset);
	~TileOnMouse();

	void Initialize();
	void Load();
	void Update(float deltaTimeMs, const sf::Vector2f& mousePos);
	void Draw(sf::RenderWindow& window);

	/// <summary>
	/// Checks if the mouse was clicked on a tile or not and what is the position of the clicked tile.
	/// </summary>
	/// <param name="tilePosition">OUT - returns the tile position of the tile clicked by the mouse.</param>
	/// <returns>Returns a boolean depending on if the mouse was clicked on tile.</returns>
	bool IsMouseClickedOnTile(sf::Vector2f &tilePosition, const sf::Vector2f& mousePosition) const;
};