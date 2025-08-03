#include "Animation.h"

Animation::Animation(std::shared_ptr<sf::Texture> texture, int frameWidth, int frameHeight, float frameTime)
    : m_texture(std::move(texture))
    , m_frameWidth(frameWidth)
    , m_frameHeight(frameHeight)
    , m_frameTime(frameTime)
    , m_currentState(State::idle_down)
    , m_currentFrame(0)
    , m_elapsedTime(0.f)
{
    loadFrames(m_currentState);
}

void Animation::applyToSprite(sf::Sprite& sprite) {
    sprite.setTexture(*m_texture);
    sprite.setTextureRect(m_frames[m_currentFrame]);
}

void Animation::setState(State state) {
    if (state != m_currentState) {
        m_currentState = state;
        m_currentFrame = 0;
        m_elapsedTime = 0.f;
        loadFrames(m_currentState);
    }
}

void Animation::update(float deltaTime) {
    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_frameTime) {
        m_elapsedTime -= m_frameTime;
        m_currentFrame = (m_currentFrame + 1) % m_frames.size();
    }
}

void Animation::loadFrames(State state) {
    m_frames.clear();

    int row = 0;
    int cols = 9;

    switch (state) {
    // ---- IDLE ----
    case State::idle_down:
        row = 0;
        m_frames.push_back(sf::IntRect(
            sf::Vector2i(0, row * m_frameHeight),
            sf::Vector2i(m_frameWidth, m_frameHeight)
        ));
        break;

    case State::idle_up:
        row = 1;
        m_frames.push_back(sf::IntRect(
            sf::Vector2i(0, row * m_frameHeight),
            sf::Vector2i(m_frameWidth, m_frameHeight)
        ));
        break;

    case State::idle_left:
        row = 2;
        m_frames.push_back(sf::IntRect(
            sf::Vector2i(0, row * m_frameHeight),
            sf::Vector2i(m_frameWidth, m_frameHeight)
        ));
        break;

    case State::idle_right:
        row = 3;
        m_frames.push_back(sf::IntRect(
            sf::Vector2i(0, row * m_frameHeight),
            sf::Vector2i(m_frameWidth, m_frameHeight)
        ));
        break;

    // ---- WALKING ----
    case State::walk_down:
        row = 0;
        for (int i = 1; i < cols; ++i) {
            m_frames.push_back(sf::IntRect(
                sf::Vector2i(i * m_frameWidth, row * m_frameHeight),
                sf::Vector2i(m_frameWidth, m_frameHeight)
            ));
        }
        break;

    case State::walk_up:
        row = 1;
        for (int i = 1; i < cols; ++i) {
            m_frames.push_back(sf::IntRect(
                sf::Vector2i(i * m_frameWidth, row * m_frameHeight),
                sf::Vector2i(m_frameWidth, m_frameHeight)
            ));
        }
        break;

    case State::walk_left:
        row = 2;
        for (int i = 1; i < cols; ++i) {
            m_frames.push_back(sf::IntRect(
                sf::Vector2i(i * m_frameWidth, row * m_frameHeight),
                sf::Vector2i(m_frameWidth, m_frameHeight)
            ));
        }
        break;

    case State::walk_right:
        row = 3;
        for (int i = 1; i < cols; ++i) {
            m_frames.push_back(sf::IntRect(
                sf::Vector2i(i * m_frameWidth, row * m_frameHeight),
                sf::Vector2i(m_frameWidth, m_frameHeight)
            ));
        }
        break;
    }
}

