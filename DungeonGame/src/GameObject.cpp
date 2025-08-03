#include "GameObject.h"
#include <iostream>
#include <unordered_map>
#include <memory>
#include <algorithm>

bool GameObject::initialiseSprite(const std::string& filename)
{
    auto tex = loadTexture(filename);
    if (!tex) {
        std::cerr << "failed to load texture - missing file/path??" << filename << "\n";
        return false;
    }

    // construct sprite directly sfml 3.0 change
    sprite = std::make_unique<sf::Sprite>(*tex);
    texture = tex; // retain ownership so it doesn't expire while sprite exists
    return true;
}


// basically the same as window.draw in game but chooses a target
void GameObject::draw(sf::RenderTarget& target) const
{
    if (sprite)
        target.draw(*sprite);
}

// getting and setting position of objects from their sprite
void GameObject::setPosition(const sf::Vector2f& pos)
{
    if (sprite)
        sprite->setPosition(pos);
}

sf::Vector2f GameObject::getPosition() const
{
    return sprite ? sprite->getPosition() : sf::Vector2f{};
}

// get sprite dimentions
sf::FloatRect GameObject::getGlobalBounds() const
{
    return sprite ? sprite->getGlobalBounds() : sf::FloatRect{};
}

std::shared_ptr<sf::Texture> GameObject::loadTexture(const std::string& filename)
{
    static std::unordered_map<std::string, std::weak_ptr<sf::Texture>> cache;

    auto it = cache.find(filename);
    if (it != cache.end()) {
        if (auto existing = it->second.lock()) {
            return existing;
        }
        // expired, fall through to reload
    }

    auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(filename)) {
        return nullptr;
    }

    // additions like texture smoothing
    tex->setSmooth(true);

    cache[filename] = tex;
    return tex;
}
