#pragma once
#include <sqlite3.h>

class Seeder {
public:
    static void insertTestLevel(sqlite3* db);
};
