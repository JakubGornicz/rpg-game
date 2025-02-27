#pragma once
#include <SFML/Graphics.hpp>
class Bullet
{
private:
	sf::Vector2i bulletSize;
	sf::Vector2f position;

public:
	sf::Texture bulletTexture;
	sf::RectangleShape bulletShape;
	sf::Vector2f mousePos;
	sf::Vector2f direction;
	sf::Vector2f rotation;
	sf::Clock fireClock;
	float bulletSpeed;

public:
	Bullet();
	~Bullet();

	void SetPosition(sf::Vector2f newPos);
	sf::Vector2f GetPosition();

	void Initialize(const sf::Vector2f& position, sf::Vector2f& target, float speed);
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);
};

