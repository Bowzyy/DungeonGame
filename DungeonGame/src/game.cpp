#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Game::~Game()
{
}

bool Game::init()
{
    std::cout << "Game initialised!" << std::endl;
    map.load("assets/maps/busstop.tmx", "assets/tilesets/tileset.png");
    return true;
}

void Game::update(float dt)
{
    // Update game logic
}

void Game::render()
{
    window.draw(map);
}


// controls

void Game::mousePressed(const sf::Event& event)
{
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseEvent->button == sf::Mouse::Button::Left)
        {
            std::cout << "Left mouse button pressed at ("
                << mouseEvent->position.x << ", "
                << mouseEvent->position.y << ")\n";
        }
        else if (mouseEvent->button == sf::Mouse::Button::Right)
        {
            std::cout << "Right mouse button pressed\n";
        }
    }
}

void Game::mouseReleased(const sf::Event& event)
{
    if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
    {
        std::cout << "Mouse button released at ("
            << mouseEvent->position.x << ", "
            << mouseEvent->position.y << ")\n";
    }
}


void Game::keyPressed(const sf::Event& event)
{
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
    {
        if (keyEvent->scancode == sf::Keyboard::Scan::A)
            std::cout << "A pressed\n";
    }
}

void Game::keyReleased(const sf::Event& event)
{
    if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>())
    {
        if (keyEvent->scancode == sf::Keyboard::Scan::A)
            std::cout << "A Released\n";
    }
}
