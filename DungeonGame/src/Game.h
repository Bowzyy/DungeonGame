#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>


#include "TileMap.h"
#include "GameObject.h"
#include "Player.h"

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

    // player
    // player is a shared pointer as its accessed by multiple parts in the game
    std::shared_ptr<Player> player;
    
    sf::View view; // camera to follow the player
};
