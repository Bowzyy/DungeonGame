#include "Player.h"

Player::Player(const sf::Vector2f& startPos, float speed)
    : move_speed(speed)
{
    setPosition(startPos);
}

// get key data from game and transform into movement
void Player::onKeyPressed(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::A:
        current_direction = Direction::Left;
        break;
    case sf::Keyboard::Key::D:
        current_direction = Direction::Right;
        break;
    case sf::Keyboard::Key::W:
        current_direction = Direction::Up;
        break;
    case sf::Keyboard::Key::S:
        current_direction = Direction::Down;
        break;
    default:
        break;
    }
}

void Player::onKeyReleased(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::A:
        if (current_direction == Direction::Left) current_direction = Direction::None;
        break;
    case sf::Keyboard::Key::D:
        if (current_direction == Direction::Right) current_direction = Direction::None;
        break;
    case sf::Keyboard::Key::W:
        if (current_direction == Direction::Up) current_direction = Direction::None;
        break;
    case sf::Keyboard::Key::S:
        if (current_direction == Direction::Down) current_direction = Direction::None;
        break;
    default:
        break;
    }
}

void Player::update(float dt)
{
    sf::Vector2f delta{ 0.f, 0.f };
    switch (current_direction) {
    case Direction::Left:
        delta.x = -move_speed * dt;
        break;
    case Direction::Right:
        delta.x = move_speed * dt;
        break;
    case Direction::Up:
        delta.y = -move_speed * dt;
        break;
    case Direction::Down:
        delta.y = move_speed * dt;
        break;
    default:
        break;
    }

    if (delta.x != 0.f || delta.y != 0.f) {
        setPosition(getPosition() + delta);
    }
}
