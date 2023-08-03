#ifndef __LIB_DB_USER_HPP
#define __LIB_DB_USER_HPP

#include <string>
#include <iostream>
#include <vector>
#include "../db/database.hpp"
#include "../exception/exception.hpp"

class User {
public:
    User();
    User(const std::string& email, const std::string& password, const std::string& name, const std::string& userType);
    ~User();
    std::string getEmail() const;
    std::string getPassword() const;
    std::string getName() const;
    std::string getUserType() const;
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    void setName(const std::string& name);
    void setUserType(const std::string& userType);
    bool operator==(const User& user) const;
    bool operator!=(const User& user) const;
private:
    std::string email;
    std::string password;
    std::string name;
    std::string userType;
};

class UserDao {
public:
    UserDao(Database& db);
    ~UserDao();
    bool insert(const User& user);
    bool update(const User& user);
    bool remove(const User& user);
    User findByEmail(const std::string& email);
    bool verify(const std::string& email, const std::string& hashPassword);
    std::vector<User> findAll();
private:
    Database db;
};

#endif // __LIB_DB_USER_HPP