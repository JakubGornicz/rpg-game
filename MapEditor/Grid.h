#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
private:
	sf::RectangleShape* hLine;
	sf::RectangleShape* vLine;

	sf::Vector2f position;
	sf::Vector2i cellSize;
	sf::Vector2i scale;

	sf::Vector2i totalCells;
	sf::Vector2i totalLines;

	sf::Color color;
	int lineThickness;

public:
	Grid(const sf::Vector2i& cellNumber,
		 const sf::Vector2i& cellSize,
		 const sf::Vector2i& scale,
		 const sf::Vector2f& position,
		 const sf::Color& color,
		 int lineThickness
		);
	~Grid();

	void Initialize();
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);

	inline const sf::Vector2i& GetTotalCells() const { return totalCells; }
};

