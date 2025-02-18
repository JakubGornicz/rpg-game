#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Skeleton.h"

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

	// temporarily here, move to player class later
    sf::Clock fireClock;
    float fireRate = 0.5f; // <- minimal time between shots

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

        // handle sprite acctivity
		skeleton.Update();
        player.Update(skeleton, fireClock, fireRate);
        
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