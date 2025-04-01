#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <sqlite3.h>
#include "Enemy.hpp"
#include "Tower.hpp"  

class Game {
public:
    Game();
    ~Game();
    void run();

    static int getTileSize() { return TILE_SIZE; }  // Getter for TILE_SIZE

private:
    void initTiles();
    void loadLevelPath();
    void spawnEnemy();
    void handleEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    std::vector<sf::RectangleShape> tiles;
    std::vector<sf::Vector2f> path;
    std::vector<Enemy> enemies;
    std::vector<Tower> towers; 
    sf::Clock clock, spawnClock;

    sqlite3* db;

    static const int TILE_SIZE = 64;
    float spawnInterval = 2.0f;
};
