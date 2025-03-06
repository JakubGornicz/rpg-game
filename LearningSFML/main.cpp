#include <SFML/Graphics.hpp>
#include <iostream>

#include "Map.h"
#include "Player.h"
#include "Skeleton.h"

int main()
{
    // Creating the window
    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML shapes", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(360);

    // Creating Text
    sf::Text fpsCounter;
    sf::Font textFont;

	// Creating Game Objects
    Player player;
    Skeleton skeleton;
    Map map;

	// INICJAIZLIZING GAME OBJECTS
    map.Initialize();
	player.Initialize(windowWidth, windowHeight);
	skeleton.Initialize();

    // Loading Text Font
    if (textFont.loadFromFile("Assets/Fonts/arial.ttf"))
    {
        std::cout << "Font loaded succesfully!" << std::endl;
        fpsCounter.setFont(textFont);
    }
    else
    {
        std::cout << "Font failed to load." << std::endl;
    }

    // LOADING GAME OBJECTS
    map.Load();
    player.Load();
    skeleton.Load();

	// MAIN GAME LOOP
    sf::Clock clock;
	sf::Clock fpsClock;
    while (window.isOpen())
    {
        // compute the framerate
        sf::Time deltaTime = clock.restart();
        float deltaTimeMs = deltaTime.asMicroseconds() / 1000.0f;

        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
        {
            int fps =  (1000.0f / deltaTimeMs);
            fpsCounter.setString("FPS: " + std::to_string(fps));
			fpsClock.restart();
        }
        
        // handle window events 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // mouse position
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// UPDATING GAME OBJECTS
        map.Update(deltaTimeMs);
		skeleton.Update(deltaTimeMs);
        player.Update(deltaTimeMs, skeleton, mousePos);
        
		// DRAWING GAME OBJECTS
        window.clear(sf::Color::Red);
        map.Draw(window);
		skeleton.Draw(window);
        player.Draw(window);
        window.draw(fpsCounter);
        window.display();
    }
    return 0;
}