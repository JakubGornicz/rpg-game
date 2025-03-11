#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "Grid.h"
#include "TileOnMouse.h"

int main()
{
    // Creating the window
    const unsigned int windowWidth = 1920;
    const unsigned int windowHeight = 1080;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML shapes", sf::Style::Default, settings);
    window.setFramerateLimit(360);

    // Creating Map Editor Objects
    Grid grid(sf::Vector2i(6, 3), // (x, y) cell number 
              sf::Vector2i(16, 16), // (x, y) cell size 
              sf::Vector2i(10, 10), // (x, y) scale 
              sf::Vector2f(0, 0), // (x, y) position
              sf::Color(255, 255, 255, 128), // grid color
              2 // line thickness
             );

    TileOnMouse tileOnMouse(sf::Vector2i(16, 16), sf::Vector2f(10, 10), sf::Vector2f(100, 100));

    sf::Text fpsCounter;
    sf::Font textFont;

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
    // INITIALISING 
    grid.Initialize();
    tileOnMouse.Initialize();


    grid.Load();
    tileOnMouse.Load();

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
            int fps = (1000.0f / deltaTimeMs);
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
        grid.Update(deltaTimeMs);
        tileOnMouse.Update(deltaTimeMs, mousePos);

        // DRAWING 
        window.clear(sf::Color::Black);
        grid.Draw(window);
        tileOnMouse.Draw(window);
        window.display();
    }
    return 0;
}