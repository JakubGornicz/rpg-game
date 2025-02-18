#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

static sf::Vector2f NormalizeVector(sf::Vector2f& vector)
{
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	vector.x /= length;
	vector.y /= length;

    return vector;
}
float AngleBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2)
{
	float dotProduct = vector1.x * vector2.x + vector1.y * vector2.y;
	float determinant = vector1.x * vector2.y - vector1.y * vector2.x;
	float angle = std::atan2(determinant, dotProduct);
	return angle;
}
int main()
{
#pragma region window
    // initialise variables
    unsigned int windowWidth = 1920;
    unsigned int windowHeight = 1080;
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML shapes", sf::Style::Fullscreen, settings);
#pragma endregion
#pragma region load textures
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	if (backgroundTexture.loadFromFile("Assets/Background/Textures/backgroundGrass.png"))
	{
		std::cout << "Background texture loaded!" << std::endl;
		backgroundSprite.setTexture(backgroundTexture);

		// resize background to fit window dynamically 
        float backgroundWidth = backgroundSprite.getGlobalBounds().width;
        float backgroundWidthScale = windowWidth / backgroundWidth;
        float backgroundHeight = backgroundSprite.getGlobalBounds().height;
        float backgroundHeightScale = windowHeight / backgroundHeight;
        backgroundSprite.setScale(sf::Vector2f(backgroundWidthScale, backgroundHeightScale));
	}
	else
	{
		std::cout << "Background texture failed to load!" << std::endl;
	}

#pragma region skeleton
    sf::Texture skeletonTexture;
    sf::Sprite skeletonSprite;
    if (skeletonTexture.loadFromFile("Assets/Skeleton/Textures/skeletonSpritesheet.png"))
    {
        std::cout << "Enemy texture loaded!" << std::endl;
        skeletonSprite.setTexture(skeletonTexture);
        skeletonSprite.setPosition(sf::Vector2f(200, 600));

        int xIndex = 0;
        int yIndex = 2;
        skeletonSprite.setTextureRect(sf::IntRect(xIndex * 64, yIndex * 64, 64, 64));
        skeletonSprite.scale(sf::Vector2f(3, 3));
    }
    else
    {
        std::cout << "Enemy texture failed to load!" << std::endl;
    }
#pragma endregion
#pragma region player
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    if (playerTexture.loadFromFile("Assets/Player/Textures/playerSpritesheet.png"))
    {
        std::cout << "Player texture loaded!" << std::endl;
	    playerSprite.setTexture(playerTexture);
        int xIndex = 0;
        int yIndex = 0;
		playerSprite.setTextureRect(sf::IntRect(xIndex * 64, yIndex * 64, 64, 64));
        playerSprite.scale(sf::Vector2f(3, 3));
        playerSprite.setPosition(sf::Vector2f(1650, 800));
    }
    else
    {
		std::cout << "Player texture failed to load!" << std::endl;
    }
#pragma endregion
#pragma region bullets
    sf::Texture bulletTexture;
    std::vector<sf::RectangleShape> bullets;

	if (bulletTexture.loadFromFile("Assets/Bullets/Textures/arrow.png"))
	{
		std::cout << "Bullet texture loaded!" << std::endl;
	}
	else
	{
		std::cout << "Bullet texture failed to load!" << std::endl;
	}

	float bulletSpeed = 0.5f;


#pragma endregion
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
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }


        float spriteHeight = playerSprite.getGlobalBounds().height;
        float spriteWidth = playerSprite.getGlobalBounds().width;
        
        // handle user input
        sf::Vector2f currentPosition = playerSprite.getPosition();
        float movementSpeed = 0.5f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (currentPosition.x < windowWidth - spriteWidth)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(movementSpeed, 0));
				playerSprite.setTextureRect(sf::IntRect(0, 3 * 64, 64, 64));			
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (currentPosition.x > 0)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(-movementSpeed, 0));
                playerSprite.setTextureRect(sf::IntRect(0, 1 * 64, 64, 64));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (currentPosition.y > 0)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(0, -movementSpeed));
                playerSprite.setTextureRect(sf::IntRect(0, 0 * 64, 64, 64));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (currentPosition.y < windowHeight - spriteHeight)
            {
                playerSprite.setPosition(currentPosition + sf::Vector2f(0, movementSpeed));
                playerSprite.setTextureRect(sf::IntRect(0, 2 * 64, 64, 64));
            }
        }

        // handle mouse
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::RectangleShape newBullet(sf::Vector2f(62, 10));
            bullets.push_back(newBullet);
			int index = bullets.size() - 1;
            bullets[index].setPosition(sf::Vector2f(playerSprite.getPosition()));
        }

        // sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        for (int i = 0; i < bullets.size(); i++)
        {
            bullets[i].setTexture(&bulletTexture);
			// FINISH THIS
            // float bulletAngle = AngleBetweenVectors(skeletonSprite.getPosition(), bullets[i].getPosition());
			// bullets[i].setRotation(bulletAngle * 180 / 3.14159265);
            sf::Vector2f bulletTarget = skeletonSprite.getPosition() - bullets[i].getPosition();
            bulletTarget = NormalizeVector(bulletTarget);
            bullets[i].setPosition(bullets[i].getPosition() + bulletTarget * bulletSpeed);
        }

        window.clear(sf::Color::Black);

		window.draw(backgroundSprite);
		window.draw(skeletonSprite);
        window.draw(playerSprite);
        for (int i = 0; i < bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }
        window.display();

    }
#pragma endregion
    return 0;
}