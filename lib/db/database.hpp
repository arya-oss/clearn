#ifndef __LIB_DB_DATABASE_HPP
#define __LIB_DB_DATABASE_HPP

#include <string>
#include <sqlite3.h>

class Database {
private:
    sqlite3* db;
public:
    Database();
    ~Database();
    bool open(const std::string& filename);
    void exec(const std::string& sql);
    void close();
};

#endif  // __LIB_DB_DATABASE_HPP