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
    // Load textures, initialise variables, etc.

    // ---- PLAYER ----
    player = std::make_shared<Player>(sf::Vector2f{ 100.f, 100.f }, 1000.0f);
    player->initialiseSprite("assets/player.png");

    // ---- CAMERA ----
    view = window.getView();
    view.zoom(0.25);

    std::cout << "Game initialised!\n";
    return true;
}

void Game::update(float dt)
{
    player->update(dt);
    view.setCenter(player->getPosition());
}

void Game::render()
{
    window.setView(view);
    window.draw(map);
    player->draw(window);
    
    // Draw your objects
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
    if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
        player->onKeyPressed(keyEvent->code);
    }
}

void Game::keyReleased(const sf::Event& event)
{
    if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>()) {
        player->onKeyReleased(keyEvent->code);
    }
}


