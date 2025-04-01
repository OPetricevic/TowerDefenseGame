#include "../../include/game/Tower.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Assume TILE_SIZE should be passed to the function
const float Tower::SIZE = 64.f;  // Define SIZE

Tower::Tower(sf::Vector2f position) : position(position) {
    shape.setRadius(Tower::SIZE / 2);  // Set radius to half the size for proper circle
    shape.setPosition(position.x - Tower::SIZE / 2, position.y - Tower::SIZE / 2);  // Center the circle on position
    shape.setFillColor(sf::Color::Blue);  // Set color of the tower
}

void Tower::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Tower::getPosition() const {
    return position;
}

namespace TowerUtils {
    bool canPlaceTower(sf::Vector2i gridPos, const std::vector<sf::Vector2f>& enemyPathGrid, const std::vector<Tower>& existingTowers, int TILE_SIZE) {
        // Check if tower is placed on path (don't allow)
        for (const auto& pathPos : enemyPathGrid) {
            // Convert grid position to float for comparison
            if (pathPos == sf::Vector2f(gridPos.x * TILE_SIZE, gridPos.y * TILE_SIZE)) {
                return false;
            }
        }

        // Ensure towers are not too close (1 tile apart)
        for (const auto& tower : existingTowers) {
            float distance = sqrt(pow(tower.getPosition().x - gridPos.x * TILE_SIZE, 2) +
                                  pow(tower.getPosition().y - gridPos.y * TILE_SIZE, 2));
            if (distance < Tower::SIZE + 1) { // If towers are too close
                return false;
            }
        }

        return true;
    }
}

