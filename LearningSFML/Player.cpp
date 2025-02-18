#include "Player.h"
#include "Skeleton.h"
#include "Math.h"
#include <iostream>

void Player::Initialize()
{
}

void Player::Load()
{
    // Loading player texture
    if (texture.loadFromFile("Assets/Player/Textures/playerSpritesheet.png"))
    {
        std::cout << "Player texture loaded!" << std::endl;
        sprite.setTexture(texture);
        int xIndex = 0;
        int yIndex = 0;
        sprite.setTextureRect(sf::IntRect(xIndex * 64, yIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(3, 3));
        sprite.setPosition(sf::Vector2f(1650, 800));
    }
    else
    {
        std::cout << "Player texture failed to load!" << std::endl;
    }

	// Loading bullet texture
    if (bulletTexture.loadFromFile("Assets/Bullets/Textures/arrow.png"))
    {
        std::cout << "Bullet texture loaded!" << std::endl;
    }
    else
    {
        std::cout << "Bullet texture failed to load!" << std::endl;
    }
}

void Player::Update(Skeleton& skeleton)
{
    float spriteHeight = sprite.getGlobalBounds().height;
    float spriteWidth = sprite.getGlobalBounds().width;

    // handle user input
    sf::Vector2f currentPosition = sprite.getPosition();
    float movementSpeed = 0.5f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (currentPosition.x < 1920 - spriteWidth)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(movementSpeed, 0));
            sprite.setTextureRect(sf::IntRect(0, 3 * 64, 64, 64));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (currentPosition.x > 0)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(-movementSpeed, 0));
            sprite.setTextureRect(sf::IntRect(0, 1 * 64, 64, 64));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (currentPosition.y > 0)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(0, -movementSpeed));
            sprite.setTextureRect(sf::IntRect(0, 0 * 64, 64, 64));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (currentPosition.y < 1080 - spriteHeight)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(0, movementSpeed));
            sprite.setTextureRect(sf::IntRect(0, 2 * 64, 64, 64));
        }
    }

    // handle shooting
    // handle mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::RectangleShape newBullet(sf::Vector2f(62, 10));
        bullets.push_back(newBullet);
        int index = bullets.size() - 1;
        bullets[index].setPosition(sf::Vector2f(sprite.getPosition()));
    }

    // sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].setTexture(&bulletTexture);
        // FINISH THIS
        // float bulletAngle = AngleBetweenVectors(skeletonSprite.getPosition(), bullets[i].getPosition());
        // bullets[i].setRotation(bulletAngle * 180 / 3.14159265);
        sf::Vector2f bulletTarget = skeleton.sprite.getPosition() - bullets[i].getPosition();
        bulletTarget = Math::NormalizeVector(bulletTarget);
        bullets[i].setPosition(bullets[i].getPosition() + bulletTarget * bulletSpeed);

		if (bullets[i].getPosition() == skeleton.sprite.getPosition())
		{
			bullets.erase(bullets.begin() + i);
		}
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    for (int i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets[i]);
    }
}
