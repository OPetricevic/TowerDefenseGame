#pragma once
#include <sqlite3.h>

class Migration {
public:
    static void run(sqlite3* db);
};