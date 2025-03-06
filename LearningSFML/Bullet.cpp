#include "Bullet.h"
#include "Math.h"
#include <iostream>

Bullet::Bullet() : 
	bulletSize(sf::Vector2i(62, 10)), bulletSpeed(0), bulletTexture(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::SetPosition(sf::Vector2f newPos)
{
    position = newPos;
}

sf::Vector2f Bullet::GetPosition()
{
    return position;
}

sf::RectangleShape& Bullet::GetShape()
{
    return bulletShape;
}

bool Bullet::IsOutOfBounds(unsigned int windowWidth, unsigned int windowHeight)
{
    sf::Vector2f pos = bulletShape.getPosition();
    return pos.x < 0 || pos.x > windowWidth || pos.y < 0 || pos.y > windowHeight;
}

void Bullet::SetTexture(sf::Texture* texture)
{
	bulletTexture = texture;
	bulletShape.setTexture(bulletTexture);
}

void Bullet::Initialize(const sf::Vector2f& position, const sf::Vector2f& target, float speed)
{
    this->bulletSpeed = speed;
    bulletShape.setSize(sf::Vector2f(bulletSize.x, bulletSize.y));
    bulletShape.setPosition(position);
    direction = Math::NormalizeVector(target - position);

    rotation = target - position;
    float bulletAngle = std::atan2(rotation.y, rotation.x) * 180 / 3.14159265;
    bulletShape.setRotation(bulletAngle + 180.0f);
}

void Bullet::Load()
{
    // IMPLEMENT IT!
    // if (bulletTexture.loadFromFile("Assets/Bullets/Textures/arrow.png"))
    // {
    //     std::cout << "Bullet texture loaded!" << std::endl;
    //     bulletShape.setTexture(&bulletTexture);
    // 
    // }
    // else
    // {
    //     std::cout << "Bullet texture failed to load!" << std::endl;
    // }
}

void Bullet::Update(float deltaTimeMs)
{
    bulletShape.setPosition(bulletShape.getPosition() + direction * bulletSpeed * deltaTimeMs);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(bulletShape);
}
