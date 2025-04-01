#include "database/Database.hpp"
#include "database/Migration.hpp"
#include "database/Seeder.hpp"
#include <sstream>
#include <sstream>
#include <cmath>  
#include "../../include/game/Enemy.hpp" 
#include "../../include/game/Game.hpp"   

const int TILE_SIZE = 64;
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;

Game::Game() : window(sf::VideoMode(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE), "Tower Defense Start") {
    window.setFramerateLimit(60);
    db = Database::connect();
    if (!db) throw std::runtime_error("Failed to connect to DB");

    Migration::run(db);
    Seeder::insertTestLevel(db);

    initTiles();
    loadLevelPath();
}

Game::~Game() {
    sqlite3_close(db);
}

void Game::initTiles() {
    for (int y = 0; y < GRID_HEIGHT; ++y)
        for (int x = 0; x < GRID_WIDTH; ++x) {
            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
            tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            tile.setFillColor(sf::Color(200, 200, 200));
            tiles.push_back(tile);
        }
}

void Game::loadLevelPath() {
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, "SELECT path_data FROM levels LIMIT 1;", -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string pathData = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::stringstream ss(pathData);
            std::string segment;
            while (std::getline(ss, segment, ';')) {
                std::stringstream pt(segment);
                std::string xStr, yStr;
                if (std::getline(pt, xStr, ',') && std::getline(pt, yStr)) {
                    path.emplace_back(std::stof(xStr), std::stof(yStr));
                }
            }
        }
    }
    sqlite3_finalize(stmt);
}

void Game::spawnEnemy() {
    if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
        enemies.emplace_back(path);
        spawnClock.restart();
    }
}


void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2i gridPos(mousePos.x / TILE_SIZE, mousePos.y / TILE_SIZE);
                
                // Pass TILE_SIZE when calling canPlaceTower
                if (TowerUtils::canPlaceTower(gridPos, path, towers, TILE_SIZE)) {
                    // If the position is valid, place the tower
                    towers.emplace_back(sf::Vector2f(gridPos.x * TILE_SIZE + TILE_SIZE / 2, gridPos.y * TILE_SIZE + TILE_SIZE / 2));
                }
            }
        }
    }
}



void Game::update(float dt) {
    for (auto& e : enemies) e.update(dt);
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                       [](const Enemy& e) { return e.isFinished(); }),
        enemies.end());
}

void Game::render() {
    window.clear(sf::Color::Black);
    // Draw the grid
    for (auto& tile : tiles) window.draw(tile);
    // Draw the towers
    for (auto& tower : towers) {
        tower.draw(window);
    }
    // Draw the enemies
    for (auto& e : enemies) e.draw(window);
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        float dt = clock.restart().asSeconds();
        spawnEnemy();
        update(dt);
        render();
    }
}
