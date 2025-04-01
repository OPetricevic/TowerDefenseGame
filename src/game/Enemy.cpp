#include "../include/game/Enemy.hpp"
#include "../include/game/Game.hpp"
#include <cmath>

Enemy::Enemy(const std::vector<sf::Vector2f>& pathPoints) : path(pathPoints) {
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(20.f, 20.f);
    shape.setPosition(path[0]);
}

void Enemy::update(float deltaTime) {
    if (currentTarget >= path.size()) return;

    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f target = path[currentTarget];
    sf::Vector2f direction = target - pos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance < 1.f) {
        currentTarget++;
        return;
    }

    direction /= distance;
    shape.move(direction * speed * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Enemy::isFinished() const {
    return currentTarget >= path.size();
}
