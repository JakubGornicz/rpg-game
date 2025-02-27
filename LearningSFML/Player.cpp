#include "Player.h"
#include "Skeleton.h"
#include "Math.h"
#include <iostream>

void Player::Initialize()
{
    // player properties
    size = sf::Vector2i(64, 64);
    speed = 2.0f;

    // bonds rectangle properties
    bondsRect.setFillColor(sf::Color::Transparent);
    bondsRect.setOutlineThickness(1.0f);
    bondsRect.setOutlineColor(sf::Color::Red);

    // shooting properties
    fireRate = 0.5f;
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
}

void Player::Update(float deltaTimeMs, Skeleton& skeleton, sf::Vector2f& mousePos)
{
    // handle user input
    sf::Vector2f currentPosition = sprite.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (currentPosition.x < 1920 - size.x)
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
        if (currentPosition.y < 1080 - size.y)
        {
            sprite.setPosition(currentPosition + sf::Vector2f(0, 1) * speed * deltaTimeMs);
            sprite.setTextureRect(sf::IntRect(0, 2 * 64, 64, 64));
        }
    }
    
    // handle shooting on mouse click + check for cooldown
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && (fireClock.getElapsedTime().asSeconds() > fireRate))
    {
        fireClock.restart(); // reset the cooldown

        Bullet newBullet;
        newBullet.Initialize(sprite.getPosition(), mousePos, 0.5f);

        bullets.push_back(newBullet);
    }

    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        bullets[i].Update(deltaTimeMs);

        // bullet collision
        if (skeleton.getHealth() > 0)
        {
            if (Math::CheckRectCollision(bullets[i].bulletShape.getGlobalBounds(), skeleton.sprite.getGlobalBounds()))
            {
                skeleton.ChangeHealth(-10);
                bullets.erase(bullets.begin() + i);
            }
        }
    }

    // bonds rectangle movement 
    bondsRect.setPosition(sprite.getPosition());
	
    // bonds rectangle collision 
    if (Math::CheckRectCollision(sprite.getGlobalBounds(), skeleton.sprite.getGlobalBounds()))
    {
        std::cout << "Collition detected!" << std::endl;
    }
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    for (int i = 0; i < bullets.size(); i++)
        bullets[i].Draw(window);
}
