#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

#include "lib/db/database.hpp"
#include "lib/utils/hash.hpp"

void InitDatabaseSchema(Database& db) {
    std::stringstream ss;
    std::string hashPassword = sha256("admin");
    db.exec("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT NOT NULL, password TEXT NOT NULL, name TEXT NOT NULL);");
    ss << "INSERT INTO user (email, password, name) VALUES ('admin', '" << hashPassword << "', 'admin');";
    db.exec(ss.str());
}

int main(int argc, char* const argv[]) {
    Database db;
    if (!db.open("test.db")) {
        std::cerr << "Error opening database" << std::endl;
        return 1;
    }
    InitDatabaseSchema(db);
    return 0;
}