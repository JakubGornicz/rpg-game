#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h"


class Player
{
private:
	// player
	sf::Vector2i size;
	sf::Texture texture;
	sf::Texture bulletTexture;
	float speed;
	
	// bullet 
	std::vector<sf::RectangleShape> bullets;
	float bulletSpeed;
	sf::Clock fireClock;
	float fireRate;

	// boundary rect
	sf::RectangleShape bondsRect;
	

public:
	sf::Sprite sprite;

public:
	void Initialize();
	void Load();
	void Update(float deltaTimeMs, Skeleton& skeleton);
	void Draw(sf::RenderWindow& window);
};