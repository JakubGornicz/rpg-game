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

void Player::Update(Skeleton& skeleton, sf::Clock& fireClock, float& fireRate)
{
	// THIS SHOULDN'T BE HERE 
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
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireClock.getElapsedTime().asSeconds() > fireRate)
    {
        fireClock.restart(); // reset the cooldown

        sf::RectangleShape newBullet(sf::Vector2f(62, 10));
        newBullet.setPosition(sprite.getPosition());
        newBullet.setTexture(&bulletTexture);


        // bullet rotation to face the target
        sf::Vector2f direction = skeleton.sprite.getPosition() - newBullet.getPosition();
        float bulletAngle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
        newBullet.setRotation(bulletAngle + 180.0f);

        bullets.push_back(newBullet);
    }

    // sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    for (int i = 0; i < bullets.size(); i++)
    {
		// bullet movement
        sf::Vector2f bulletTarget = skeleton.sprite.getPosition() - bullets[i].getPosition();
        bulletTarget = Math::NormalizeVector(bulletTarget);
        bullets[i].setPosition(bullets[i].getPosition() + bulletTarget * bulletSpeed);
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
