#include "TileMap.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

bool TileMap::load(const std::string& tmxFile, const std::string& tilesetTexture)
{
    tmx::Map map;
    if (!map.load(tmxFile))
        return false;

    if (!tileset.loadFromFile(tilesetTexture))
        return false;

    const auto& tilesets = map.getTilesets();
    if (tilesets.empty()) return false;

    const auto& layers = map.getLayers();
    if (layers.empty()) return false;

    unsigned columns = tileset.getSize().x / tile_width;

    // clear
    layersVertices.clear();

    for (const auto& layer : layers)
    {
        if (layer->getType() != tmx::Layer::Type::Tile)
            continue; // only use tile layers

        auto tileLayer = layer->getLayerAs<tmx::TileLayer>();
        const auto& tiles = tileLayer.getTiles();

        unsigned width = tileLayer.getSize().x;
        unsigned height = tileLayer.getSize().y;

        sf::VertexArray vertices;
        vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        vertices.resize(width * height * 6);

        for (unsigned y = 0; y < height; ++y)
        {
            for (unsigned x = 0; x < width; ++x)
            {
                int tileID = tiles[y * width + x].ID;
                if (tileID == 0) continue;

                tileID -= tilesets[0].getFirstGID();

                int tu = tileID % columns - 1; // shift tilemap over (hi idk it worked in second year!))
                int tv = tileID / columns;

                float px = x * tile_width;
                float py = y * tile_height;
                float tx = tu * tile_width;
                float ty = tv * tile_height;

                sf::Vertex* tri = &vertices[(y * width + x) * 6];

                // t1
                tri[0].position = { px, py };
                tri[1].position = { px + tile_width, py };
                tri[2].position = { px + tile_width, py + tile_height };

                tri[0].texCoords = { tx, ty };
                tri[1].texCoords = { tx + tile_width, ty };
                tri[2].texCoords = { tx + tile_width, ty + tile_height };

                // t2
                tri[3].position = { px, py };
                tri[4].position = { px + tile_width, py + tile_height };
                tri[5].position = { px, py + tile_height };

                tri[3].texCoords = { tx, ty };
                tri[4].texCoords = { tx + tile_width, ty + tile_height };
                tri[5].texCoords = { tx, ty + tile_height };
            }
        }

        layersVertices.push_back(std::move(vertices));
    }

    return true;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileset;

    for (const auto& vertices : layersVertices)
    {
        target.draw(vertices, states);
    }
}

