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

    sf::Texture tileset;
    std::vector<sf::VertexArray> layersVertices;  // layers

    // size of tiles
    unsigned tile_width = 16;
    unsigned tile_height = 16;
};
