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
#include <unistd.h>

#include "lib/db/database.hpp"
#include "lib/utils/hash.hpp"
#include "lib/db/user.hpp"

void InitDatabaseSchema(Database& db) {
    std::stringstream ss;
    db.exec("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT NOT NULL, password TEXT NOT NULL, name TEXT NOT NULL, user_type TEXT NOT NULL);");
    db.exec(ss.str());
}

void displaySelfHelpChoices() {
    system("clear");
    std::cout << "1. Register" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void SelfHelp() {
    
}

int main(int argc, char* const argv[]) {
    Database db;
    if (!db.open("test.db")) {
        std::cerr << "Error in opening database!" << std::endl;
        return 1;
    }
    InitDatabaseSchema(db);
    return 0;
}