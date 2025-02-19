#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Skeleton.h"

int main()
{
	// ------------------------- INITIALIZATION -----------------------

    // Window
    unsigned int windowWidth = 1920;
    unsigned int windowHeight = 1080;
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML shapes", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    // Text
    sf::Text fpsCounter;
    sf::Font textFont;
    float timer = 0;

    // Entities
    Player player;
    Skeleton skeleton;

	player.Initialize();
	skeleton.Initialize();

    // ------------------------- INITIALIZATION -----------------------
	// ------------------------- LOAD -----------------------

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

    // Loading Entities
    player.Load();
    skeleton.Load();

    // ------------------------- LOAD -----------------------
	
    sf::Clock clock;
    while (window.isOpen())
    {
        // --------------------------- UPDATE ---------------------------
    
        // calculating time to render a single frame
        sf::Time deltaTime = clock.restart();
        float deltaTimeMs = deltaTime.asMilliseconds();

        // calculating FPS
        timer += deltaTimeMs;
        if (timer >= 100.0f)
        {
            int fps = 1000.0f / deltaTimeMs;
            std::string fpsText = "FPS: " + std::to_string(fps);
            fpsCounter.setString(fpsText);
            timer = 0;
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


        // handle sprite acctivity
		skeleton.Update(deltaTimeMs);
        player.Update(deltaTimeMs, skeleton);
        
        // --------------------------- UPDATE ---------------------------


		// --------------------------- DRAW ---------------------------
        window.clear(sf::Color::Black);
		skeleton.Draw(window);
        player.Draw(window);
        window.draw(fpsCounter);
        window.display();
        // --------------------------- DRAW ---------------------------
    }
	

    return 0;
}