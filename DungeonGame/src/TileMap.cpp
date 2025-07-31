#include "TileMap.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

bool TileMap::load(const std::string& tmxFile, const std::string& tilesetTexture)
{
    tmx::Map map;
    if (!map.load(tmxFile))
        return false;

    if (!m_tileset.loadFromFile(tilesetTexture))
        return false;

    const auto& tilesets = map.getTilesets();
    if (tilesets.empty()) return false;

    m_tileWidth = 16;
    m_tileHeight = 16;

    const auto& layers = map.getLayers();
    if (layers.empty()) return false;

    unsigned columns = m_tileset.getSize().x / m_tileWidth;

    // clear
    m_layersVertices.clear();

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

                float px = x * m_tileWidth;
                float py = y * m_tileHeight;
                float tx = tu * m_tileWidth;
                float ty = tv * m_tileHeight;

                sf::Vertex* tri = &vertices[(y * width + x) * 6];

                // t1
                tri[0].position = { px, py };
                tri[1].position = { px + m_tileWidth, py };
                tri[2].position = { px + m_tileWidth, py + m_tileHeight };

                tri[0].texCoords = { tx, ty };
                tri[1].texCoords = { tx + m_tileWidth, ty };
                tri[2].texCoords = { tx + m_tileWidth, ty + m_tileHeight };

                // t2
                tri[3].position = { px, py };
                tri[4].position = { px + m_tileWidth, py + m_tileHeight };
                tri[5].position = { px, py + m_tileHeight };

                tri[3].texCoords = { tx, ty };
                tri[4].texCoords = { tx + m_tileWidth, ty + m_tileHeight };
                tri[5].texCoords = { tx, ty + m_tileHeight };
            }
        }

        m_layersVertices.push_back(std::move(vertices));
    }

    return true;
}


void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;

    for (const auto& vertices : m_layersVertices)
    {
        target.draw(vertices, states);
    }
}

