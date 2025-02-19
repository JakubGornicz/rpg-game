#include "Skeleton.h"
#include <iostream>

void Skeleton::Initialize()
{
    size = sf::Vector2i(64, 64);

    bondsRect.setFillColor(sf::Color::Transparent);
    bondsRect.setOutlineThickness(1.0f);
    bondsRect.setOutlineColor(sf::Color::Blue);

}

void Skeleton::Load()
{
    if (texture.loadFromFile("Assets/Skeleton/Textures/skeletonSpritesheet.png"))
    {
        std::cout << "Enemy texture loaded!" << std::endl;
        sprite.setTexture(texture);
        sprite.setPosition(sf::Vector2f(200, 600));

        int xIndex = 0;
        int yIndex = 2;
        sprite.setTextureRect(sf::IntRect(xIndex * size.x, yIndex * size.y, size.x, size.y));
        // setting scale of sprite
        sprite.scale(sf::Vector2f(3, 3));

        // resizing the bondsRect to match the sprite
        bondsRect.setSize(sf::Vector2f(size.x * sprite.getScale().x, size.y * sprite.getScale().y));
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
}

void Skeleton::Update(float deltaTimeMs)
{
    bondsRect.setPosition(sprite.getPosition());
}

void Skeleton::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(bondsRect);
}
