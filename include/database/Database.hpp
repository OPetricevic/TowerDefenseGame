// include/database/Database.hpp
#pragma once
#include <sqlite3.h>
#include <string>

class Database {
public:
    static sqlite3* connect(const std::string& dbFile = "game_data.db");
};
