#pragma once
#include "GameObject.h"
#include "Animation.h"

#include <SFML/Window/Keyboard.hpp>
#include <memory>

class Player : public GameObject {
public:
    enum class Direction { None, Left, Right, Up, Down };

    Player(const std::string& filename, const sf::Vector2f& start_pos, float speed = 200.f);

    void update(float dt) override;

    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

private:
    float move_speed;
    Direction current_direction = Direction::None;
    Direction previous_direction = Direction::Down;

    std::unique_ptr<Animation> animation;
    Animation::State player_state = Animation::State::idle_down;

    void updateAnimationState();
};
