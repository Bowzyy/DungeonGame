#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    enum class State {
        idle_down,
        idle_up,
        idle_left,
        idle_right,
        walk_down,
        walk_up,
        walk_left,
        walk_right
    };

    Animation(std::shared_ptr<sf::Texture> texture, int frameWidth, int frameHeight, float frameTime);

    void setState(State state);
    void update(float deltaTime);
    void applyToSprite(sf::Sprite& sprite);

private:
    std::shared_ptr<sf::Texture> m_texture; // own/share to keep alive
    int m_frameWidth, m_frameHeight;
    float m_frameTime;

    State m_currentState;
    int m_currentFrame;
    float m_elapsedTime;

    std::vector<sf::IntRect> m_frames;

    void loadFrames(State state);
};

#endif // ANIMATION_H
