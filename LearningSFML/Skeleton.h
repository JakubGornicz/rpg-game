#pragma once
#include <SFML/Graphics.hpp>
class Skeleton
{
private:
	sf::Texture texture;

public:
	sf::Sprite sprite;

	sf::RectangleShape bondsRect;
	sf::Vector2i size;

public:
	void Initialize();
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);
};

