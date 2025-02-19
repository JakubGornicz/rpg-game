#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h"


class Player
{
private:
	sf::Vector2i size;
	sf::Texture texture;
	sf::Texture bulletTexture;
	float speed;
	
	std::vector<sf::RectangleShape> bullets;
	float bulletSpeed;

	sf::RectangleShape bondsRect;
	

public:
	sf::Sprite sprite;

public:
	void Initialize();
	void Load();
	void Update(float deltaTimeMs, Skeleton& skeleton, sf::Clock& fireClock, float& fireRate);
	void Draw(sf::RenderWindow& window);
};