#include "Player.h"
#include "Skeleton.h"
#include "Math.h"
#include <iostream>

void Player::Initialize()
{
    size = sf::Vector2i(64, 64);
    speed = 2.0f;

    bulletSpeed = 1.5f;

    bondsRect.setFillColor(sf::Color::Transparent);
    bondsRect.setOutlineThickness(1.0f);
    bondsRect.setOutlineColor(sf::Color::Red);


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
        sprite.setTextureRect(sf::IntRect(xIndex * size.x, yIndex * size.y, size.x, size.y));
        sprite.setPosition(sf::Vector2f(1650, 800));

        // setting scale of sprite
        sprite.scale(sf::Vector2f(3, 3));

        // resizing the bondsRect to match the sprite
        bondsRect.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
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

void Player::Update(float deltaTimeMs, Skeleton& skeleton, sf::Clock& fireClock, float& fireRate)
{
	// THIS SHOULDN'T BE HERE 
    float spriteHeight = sprite.getGlobalBounds().height;
    float spriteWidth = sprite.getGlobalBounds().width;

    // handle user input
    sf::Vector2f currentPosition = sprite.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (currentPosition.x < 1920 - spriteWidth)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(1, 0) * speed * deltaTimeMs);
            sprite.setTextureRect(sf::IntRect(0, 3 * 64, 64, 64));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (currentPosition.x > 0)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(-1, 0) * speed * deltaTimeMs);
            sprite.setTextureRect(sf::IntRect(0, 1 * 64, 64, 64));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (currentPosition.y > 0)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(0, -1) * speed * deltaTimeMs);
            sprite.setTextureRect(sf::IntRect(0, 0 * 64, 64, 64));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (currentPosition.y < 1080 - spriteHeight)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(0, 1) * speed * deltaTimeMs);
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
        bullets[i].setPosition(bullets[i].getPosition() + bulletTarget * bulletSpeed * deltaTimeMs);
    }

    // Bonds rectangle movement 
    bondsRect.setPosition(sprite.getPosition());


    if (Math::CheckRectCollision(sprite.getGlobalBounds(), skeleton.sprite.getGlobalBounds()))
    {
        std::cout << "Collition detected!" << std::endl;
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(bondsRect);

    for (int i = 0; i < bullets.size(); i++)
    {
        window.draw(bullets[i]);
    }
}
