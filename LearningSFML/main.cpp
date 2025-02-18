#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Skeleton.h"


static float AngleBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2)
{
	float dotProduct = vector1.x * vector2.x + vector1.y * vector2.y;
	float determinant = vector1.x * vector2.y - vector1.y * vector2.x;
	float angle = std::atan2(determinant, dotProduct);
	return angle;
}
int main()
{
	// ------------------------------------------------------ INITIALIZATION ------------------------------------------------------
    unsigned int windowWidth = 1920;
    unsigned int windowHeight = 1080;
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML shapes", sf::Style::Fullscreen, settings);

    Player player;
    Skeleton skeleton;

	player.Initialize();
	skeleton.Initialize();

    // ------------------------------------------------------ INITIALIZATION ------------------------------------------------------
	// ----------------------------------------------------------- LOAD -----------------------------------------------------------

    player.Load();
    skeleton.Load();

    // ----------------------------------------------------------- LOAD -----------------------------------------------------------
	

    while (window.isOpen())
    {
        // ----------------------------------------------------------- UPDATE -----------------------------------------------------------
        // handle window events 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

		skeleton.Update();
        player.Update(skeleton);
        
        // ----------------------------------------------------------- UPDATE -----------------------------------------------------------

		// ----------------------------------------------------------- DRAW -----------------------------------------------------------
        window.clear(sf::Color::Black);
		skeleton.Draw(window);
        player.Draw(window);
        window.display();
        // ----------------------------------------------------------- DRAW -----------------------------------------------------------
    }
	

    return 0;
}