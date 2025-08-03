#pragma once
#include "GameObject.h"
#include <SFML/Window/Keyboard.hpp>

class Player : public GameObject {
public:
    enum class Direction { None, Left, Right, Up, Down };

    Player(const sf::Vector2f& startPos, float speed = 200.f);

    void update(float dt) override;

    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

private:
    float move_speed;
    Direction current_direction = Direction::None;
};
