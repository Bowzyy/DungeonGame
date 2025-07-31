#include "TileMap.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

bool TileMap::load(const std::string& tmxFile, const std::string& tilesetTexture)
{
    // get map data
    tmx::Map map;
    if (!map.load(tmxFile))
        return false;

    // load the texture
    if (!m_tileset.loadFromFile(tilesetTexture))
        return false;

    // Assume the first tileset and first layer for simplicity
    const auto& tilesets = map.getTilesets();
    if (tilesets.empty()) return false;

    m_tileWidth = 16;
    m_tileHeight = 16;

    const auto& layers = map.getLayers();
    if (layers.empty()) return false;

    auto tileLayer = layers[0]->getLayerAs<tmx::TileLayer>();
    const auto& tiles = tileLayer.getTiles();

    // Prepare vertex array
    unsigned width = tileLayer.getSize().x;
    unsigned height = tileLayer.getSize().y;

    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    m_vertices.resize(width * height * 4);

    unsigned columns = m_tileset.getSize().x / m_tileWidth;

    m_vertices.resize(width * height * 6);

    for (unsigned y = 0; y < height; ++y)
    {
        for (unsigned x = 0; x < width; ++x)
        {
            int tileID = tiles[y * width + x].ID;
            if (tileID == 0) continue;

            tileID -= tilesets[0].getFirstGID();

            int tu = tileID % columns -1; // move one tile over (idk why i did it in second year too lol)
            int tv = tileID / columns;

            float px = x * m_tileWidth;
            float py = y * m_tileHeight;
            float tx = tu * m_tileWidth;
            float ty = tv * m_tileHeight;

            // Get 6 vertices (2 triangles)
            sf::Vertex* tri = &m_vertices[(y * width + x) * 6];

            // Triangle 1
            tri[0].position = { px, py };
            tri[1].position = { px + m_tileWidth, py };
            tri[2].position = { px + m_tileWidth, py + m_tileHeight };

            tri[0].texCoords = { tx, ty };
            tri[1].texCoords = { tx + m_tileWidth, ty };
            tri[2].texCoords = { tx + m_tileWidth, ty + m_tileHeight };

            // Triangle 2
            tri[3].position = { px, py };
            tri[4].position = { px + m_tileWidth, py + m_tileHeight };
            tri[5].position = { px, py + m_tileHeight };

            tri[3].texCoords = { tx, ty };
            tri[4].texCoords = { tx + m_tileWidth, ty + m_tileHeight };
            tri[5].texCoords = { tx, ty + m_tileHeight };
        }
    }


    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}
