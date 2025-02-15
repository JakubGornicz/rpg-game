#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main()
{
#pragma region random

    sf::Time t1 = sf::milliseconds(1000);
    sf::Time t2 = sf::seconds(5);

    sf::Clock clock;
    // clock.start();
#pragma endregion

    // initialise variables
    unsigned int width = 1200;
    unsigned int height = 800;
    sf::ContextSettings settings; 
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({ width, height }), "SFML shapes", sf::Style::Default, settings);

    float size = std::abs(50.0f);
    sf::CircleShape circle(size);
    circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(sf::Vector2f(width / 2, height / 2));


    sf::RectangleShape rectangle(sf::Vector2f(100, 50));
    rectangle.setOrigin(sf::Vector2f(rectangle.getSize() / 2.0f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(sf::Vector2f(width / 2, height / 2 + 200));
    rectangle.setRotation(45);

    sf::CircleShape triangle(80.0f, 3);
    triangle.setOrigin(sf::Vector2f(triangle.getRadius(), triangle.getRadius()));
    triangle.setFillColor(sf::Color::Red);
    triangle.setPosition(sf::Vector2f(width / 2, height / 2 - 200));
    triangle.setRotation(90);

    sf::CircleShape square(80.0f, 4);
    square.setOrigin(sf::Vector2f(square.getRadius(), square.getRadius()));
    square.setFillColor(sf::Color::Blue);
    square.setPosition(sf::Vector2f(width / 2 + 200, height / 2));
    //square.setRotation(sf::degrees(45));

    sf::CircleShape sextagon(80.0f, 6);
    sextagon.setOrigin(sf::Vector2f(sextagon.getRadius(), sextagon.getRadius()));
    sextagon.setFillColor(sf::Color::Magenta);
    sextagon.setPosition(sf::Vector2f(width / 2 - 200, height / 2));


    // main game loop
    while (window.isOpen())
    {
        // handle window events 
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(square);
        window.draw(sextagon);
        window.display();

    }

    return 0;
}