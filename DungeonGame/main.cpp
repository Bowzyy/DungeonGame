#include <iostream>
#include <SFML/Graphics.hpp>
#include "src/Game.h"

int main()
{
    std::cout << "You should see a window that opens as well as this writing to console..." << std::endl;

    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "Dungeon Game");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Game game(window);

    if (!game.init())
    {
        return 0;
    }

    // game loop
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // periferals
            if (event->is<sf::Event::KeyPressed>())
                game.keyPressed(*event);

            if (event->is<sf::Event::KeyReleased>())
                game.keyReleased(*event);

            if (event->is<sf::Event::MouseButtonPressed>())
                game.mousePressed(*event);

            if (event->is<sf::Event::MouseButtonReleased>())
                game.mouseReleased(*event);
        }

        // game update
        game.update(dt);

        // clear screen and render game
        window.clear(sf::Color::Black);
        game.render();
        window.display();
    }


    return 0;
}

