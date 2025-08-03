#include "Player.h"

Player::Player(const sf::Vector2f& startPos, float speed)
    : moveSpeed(speed)
{
    setPosition(startPos);
}

// get key data from game and transform into movement
void Player::onKeyPressed(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::A:
        currentDir = Direction::Left;
        break;
    case sf::Keyboard::Key::D:
        currentDir = Direction::Right;
        break;
    case sf::Keyboard::Key::W:
        currentDir = Direction::Up;
        break;
    case sf::Keyboard::Key::S:
        currentDir = Direction::Down;
        break;
    default:
        break;
    }
}

void Player::onKeyReleased(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::A:
        if (currentDir == Direction::Left) currentDir = Direction::None;
        break;
    case sf::Keyboard::Key::D:
        if (currentDir == Direction::Right) currentDir = Direction::None;
        break;
    case sf::Keyboard::Key::W:
        if (currentDir == Direction::Up) currentDir = Direction::None;
        break;
    case sf::Keyboard::Key::S:
        if (currentDir == Direction::Down) currentDir = Direction::None;
        break;
    default:
        break;
    }
}

void Player::update(float dt)
{
    sf::Vector2f delta{ 0.f, 0.f };
    switch (currentDir) {
    case Direction::Left:
        delta.x = -moveSpeed * dt;
        break;
    case Direction::Right:
        delta.x = moveSpeed * dt;
        break;
    case Direction::Up:
        delta.y = -moveSpeed * dt;
        break;
    case Direction::Down:
        delta.y = moveSpeed * dt;
        break;
    default:
        break;
    }

    if (delta.x != 0.f || delta.y != 0.f) {
        setPosition(getPosition() + delta);
    }
}
