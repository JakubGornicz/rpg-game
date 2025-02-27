#pragma once
#include <SFML/Graphics.hpp>
class Skeleton
{
private:
	sf::Texture texture;

	int health;
	sf::Text healthText;
	sf::Font font;

public:
	sf::Sprite sprite;

	sf::RectangleShape bondsRect;
	sf::Vector2i size;

public:
	Skeleton();
	~Skeleton();

	void ChangeHealth(int hp);

	int getHealth();

	void Initialize();
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);
};

