#include "Skeleton.h"
#include <iostream>

void Skeleton::Initialize()
{
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
        sprite.setTextureRect(sf::IntRect(xIndex * 64, yIndex * 64, 64, 64));
        sprite.scale(sf::Vector2f(3, 3));
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
}

void Skeleton::Update()
{
}

void Skeleton::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
