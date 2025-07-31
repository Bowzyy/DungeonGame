#pragma once
#include <SFML/Graphics.hpp>

#include "TileMap.h"

class Game
{
public:
    Game(sf::RenderWindow& window);
    ~Game();

    bool init();
    void update(float dt);
    void render();

    // periferal inputs
    void mousePressed(const sf::Event& event);
    void mouseReleased(const sf::Event& event);
    void keyPressed(const sf::Event& event);
    void keyReleased(const sf::Event& event);

private:
    sf::RenderWindow& window;
    TileMap map;

};
