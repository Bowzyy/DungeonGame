#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default; // virtual cause will be derived

    bool initialiseSprite(const std::string& filename);

    virtual void update(float dt) {}
    virtual void draw(sf::RenderTarget& target) const;

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

protected:
    std::unique_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Texture> texture;   // moved to protected to be accessable by animation

private:

    //allows for a "cache" of textures to stop multiple reloads of the same file
    static std::shared_ptr<sf::Texture> loadTexture(const std::string& filename);
};
