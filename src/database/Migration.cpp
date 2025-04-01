#include "../../include/database/Migration.hpp"
#include <iostream>

void Migration::run(sqlite3* db) {
    //sqlite3_exec(db, "DROP TABLE IF EXISTS levels;", nullptr, nullptr, nullptr);

    const char* createLevelsTable = R"(
        CREATE TABLE levels (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            path_data TEXT NOT NULL
        );
    )";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, createLevelsTable, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "[!] Failed to run migrations: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "[*] Migrations ran successfully." << std::endl;
    }
}
