#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
#pragma region window
    // initialise variables
    unsigned int windowWidth = 960;
    unsigned int windowHeight = 640;
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML shapes", sf::Style::Default, settings);
#pragma endregion
#pragma region load textures
    sf::Texture Playertexture;
    sf::Sprite playerSprite;
    if (Playertexture.loadFromFile("Assets/Player/Textures/spritesheet.png"))
    {
        std::cout << "Player texture loaded!" << std::endl;
	    playerSprite.setTexture(Playertexture);
        int xIndex = 0;
        int yIndex = 0;
		playerSprite.setTextureRect(sf::IntRect(xIndex * 64, yIndex * 64, 64, 64));
        playerSprite.scale(sf::Vector2f(5.0f, 5.0f));
    }
    else
    {
		std::cout << "Player texture failed to load!" << std::endl;
    }
#pragma endregion
#pragma region main game loop
    while (window.isOpen())
    {
        // handle window events 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int temp = 5*64;
        // handle user input
        sf::Vector2f currentPosition = playerSprite.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (currentPosition.x < windowWidth - temp)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(1, 0));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (currentPosition.x > 0)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(-1, 0));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (currentPosition.y > 0)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(0, -1));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (currentPosition.y < windowHeight - temp)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(0, 1));
            }
        }

        window.clear(sf::Color::Black);

        window.draw(playerSprite);
        window.display();

    }
#pragma endregion
    return 0;
}