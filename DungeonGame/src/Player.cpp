#include "Player.h"
#include <stdexcept>

Player::Player(const std::string& filename, const sf::Vector2f& start_pos, float speed)
    : move_speed(speed)
{
    // Load texture and initialize sprite first
    if (!initialiseSprite(filename)) {
        throw std::runtime_error("Failed to load player texture: " + filename);
    }

    setPosition(start_pos);

    // get texture from gameobject
    animation = std::make_unique<Animation>(texture, 28, 40, 0.05f);
    player_state = Animation::State::idle_down;
    animation->setState(player_state);
}

void Player::onKeyPressed(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::A:
        current_direction = Direction::Left;
        previous_direction = current_direction;
        break;
    case sf::Keyboard::Key::D:
        current_direction = Direction::Right;
        previous_direction = current_direction;
        break;
    case sf::Keyboard::Key::W:
        current_direction = Direction::Up;
        previous_direction = current_direction;
        break;
    case sf::Keyboard::Key::S:
        current_direction = Direction::Down;
        previous_direction = current_direction;
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

void Player::updateAnimationState()
{
    Animation::State desired;

    // ---- IDLE ----
    if (current_direction == Direction::None) {
        switch (previous_direction) {
        case Direction::Left:
            desired = Animation::State::idle_left;
            break;
        case Direction::Right:
            desired = Animation::State::idle_right;
            break;
        case Direction::Up:
            desired = Animation::State::idle_up;
            break;
        case Direction::Down:
        default:
            desired = Animation::State::idle_down;
            break;
        }
    }
    // ---- WALKING ----
    else {
        switch (current_direction) {
        case Direction::Left:
            desired = Animation::State::walk_left;
            break;
        case Direction::Right:
            desired = Animation::State::walk_right;
            break;
        case Direction::Up:
            desired = Animation::State::walk_up;
            break;
        case Direction::Down:
            desired = Animation::State::walk_down;
            break;
        default:
            desired = Animation::State::idle_down;
            break;
        }
    }

    if (desired != player_state) {
        player_state = desired;
        animation->setState(player_state);
    }
}

void Player::update(float dt)
{
    // Movement
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

    // update animation
    updateAnimationState();
    animation->update(dt);

    // update player sprite based on animation
    if (sprite) {
        animation->applyToSprite(*sprite);
    }
}
