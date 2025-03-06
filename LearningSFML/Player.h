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
	sf::RectangleShape bondsRect;
	float speed;
	
	// bullets 
	sf::Vector2f mousePos;
	std::vector<Bullet> bullets;
	sf::Texture bulletTexture;
	sf::Clock fireClock;
	float fireRate;

	int windowWidth;
	int windowHeight;

public:
	sf::Sprite sprite;

public:
	Player();
	~Player();
	void Initialize(const unsigned int& windowWidth, const unsigned int& windowHeight);
	void Load();
	void Update(float deltaTimeMs, Skeleton& skeleton, const sf::Vector2f& mousePos);
	void Draw(sf::RenderWindow& window);
};