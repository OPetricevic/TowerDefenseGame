#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Tower {
public:
    static const float SIZE;  // Declare SIZE as a static constant

    Tower(sf::Vector2f position);

    void draw(sf::RenderWindow& window) const;
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape;
    sf::Vector2f position;
};

namespace TowerUtils {
    bool canPlaceTower(sf::Vector2i gridPos, const std::vector<sf::Vector2f>& enemyPathGrid, const std::vector<Tower>& existingTowers, int TILE_SIZE); 
}
