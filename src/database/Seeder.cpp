#include "../../include/database/Seeder.hpp"
#include <sstream>
#include <iostream>

void Seeder::insertTestLevel(sqlite3* db) {
    int count = 0;
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM levels;", -1, &checkStmt, nullptr);
    if (sqlite3_step(checkStmt) == SQLITE_ROW)
        count = sqlite3_column_int(checkStmt, 0);
    sqlite3_finalize(checkStmt);

    if (count > 0) return;

    std::ostringstream path;
    const int TILE_SIZE = 64;
    const int WIDTH = 10;
    const int HEIGHT = 10;
    bool leftToRight = true;

    for (int y = 0; y < HEIGHT; y += 2) {
        if (leftToRight) {
            for (int x = 0; x < WIDTH; ++x) {
                float cx = x * TILE_SIZE + TILE_SIZE / 2.0f;
                float cy = y * TILE_SIZE + TILE_SIZE / 2.0f;
                path << cx << "," << cy << ";";
            }
        } else {
            for (int x = WIDTH - 1; x >= 0; --x) {
                float cx = x * TILE_SIZE + TILE_SIZE / 2.0f;
                float cy = y * TILE_SIZE + TILE_SIZE / 2.0f;
                path << cx << "," << cy << ";";
            }
        }

        leftToRight = !leftToRight;

        if (y + 1 < HEIGHT) {
            int lastX = leftToRight ? 0 : (WIDTH - 1);
            float cx = lastX * TILE_SIZE + TILE_SIZE / 2.0f;
            float cy = (y + 1) * TILE_SIZE + TILE_SIZE / 2.0f;
            path << cx << "," << cy << ";";
        }
    }

    std::string pathStr = path.str();
    if (!pathStr.empty()) pathStr.pop_back(); // remove trailing ;

    sqlite3_stmt* stmt;
    const char* insertSQL = "INSERT INTO levels (name, path_data) VALUES (?, ?);";

    int rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "[!] Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, "Test Level", -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pathStr.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "[!] Failed to insert level: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}
