#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Bullet
{
private:
	sf::Vector2i bulletSize;
	sf::Vector2f position;
	sf::RectangleShape bulletShape;
	sf::Texture* bulletTexture;
	sf::Vector2f mousePos;
	sf::Vector2f direction;
	sf::Vector2f rotation;
	sf::Clock fireClock;
	float bulletSpeed;

public:
	// Constructors and Destructors
	Bullet();
	~Bullet();

	// Functions
	void SetPosition(sf::Vector2f newPos);
	sf::Vector2f GetPosition();
	sf::RectangleShape& GetShape();
	bool IsOutOfBounds(unsigned int windowWidth, unsigned int windowHeight);
	void SetTexture(sf::Texture* texture);

	void Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed);
	void Load();
	void Update(float deltaTimeMs);
	void Draw(sf::RenderWindow& window);

	inline const sf::FloatRect& GetGlobalBounds() { return bulletShape.getGlobalBounds(); }
};

