#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


class Enemy {
public:
    Enemy(const std::vector<sf::Vector2f>& pathPoints);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isFinished() const;

private:
    sf::CircleShape shape;
    std::vector<sf::Vector2f> path;
    std::size_t currentTarget = 0;
    float speed = 100.f;
};
