#include <iostream>
#include "database.hpp"

Database::Database() : db(nullptr) {
}

Database::~Database() {
    close();
}

void Database::close() {
    if (db != nullptr) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::open(const std::string& filename) {
    close();
    int rc = sqlite3_open(filename.c_str(), &db);
    return rc == SQLITE_OK;
}

void Database::exec(const std::string& sql) {
    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }
}