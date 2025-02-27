#pragma once
#include <SFML/Graphics.hpp>
#include "Skeleton.h"
#include "Bullet.h"

class Player
{
private:
	// player
	sf::Vector2i size;
	sf::Texture texture;
	float speed;
	
	// bullets 
	sf::Vector2f mousePos;
	std::vector<Bullet> bullets;
	sf::Clock fireClock;
	float fireRate;

	// boundary rect
	sf::RectangleShape bondsRect;

public:
	sf::Sprite sprite;

public:
	void Initialize();
	void Load();
	void Update(float deltaTimeMs, Skeleton& skeleton, sf::Vector2f& mousePos);
	void Draw(sf::RenderWindow& window);
};