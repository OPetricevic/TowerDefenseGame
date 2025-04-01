#include "../../include/database/Database.hpp"
#include <iostream>

sqlite3* Database::connect(const std::string& dbFile) {
    sqlite3* db;
    int rc = sqlite3_open(dbFile.c_str(), &db);

    if (rc) {
        std::cerr << "[!] Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    } else {
        std::cout << "[*] SQLite DB opened successfully." << std::endl;
    }
    return db;
}