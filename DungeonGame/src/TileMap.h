#pragma once
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tmxFile, const std::string& tilesetTexture);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Texture m_tileset;
    std::vector<sf::VertexArray> m_layersVertices;  // layers

    // size of tiles
    unsigned m_tileWidth = 0;
    unsigned m_tileHeight = 0;
};
