#include "user.hpp"

/**
 * @brief Construct a new User:: User object
*/
User::User() {
}

/**
 * @brief Construct a new User:: User object
*/
User::User(const std::string& email, const std::string& password, const std::string& name, const std::string& userType) : email(email), password(password), name(name), userType(userType) {
}

/**
 * @brief Destroy the User:: User object
*/
User::~User() {
}

void User::setEmail(const std::string& email) {
    this->email = email;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setName(const std::string& name) {
    this->name = name;
}

void User::setUserType(const std::string& userType) {
    this->userType = userType;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getName() const {
    return name;
}

std::string User::getUserType() const {
    return userType;
}

bool User::operator==(const User& user) const {
    return email == user.email;
}

bool User::operator!=(const User& user) const {
    return email != user.email;
}

UserDao::UserDao(Database& db) : db(db) {
}

UserDao::~UserDao() {
}

/**
 * @brief Insert a new user into database
*/
bool UserDao::insert(const User& user) {
    std::string sql = "INSERT INTO user (email, password, name, user_type) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, user.getEmail().c_str(), user.getEmail().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.getPassword().c_str(), user.getPassword().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user.getName().c_str(), user.getName().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user.getUserType().c_str(), user.getUserType().size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

/**
 * @brief Update user information
*/
bool UserDao::update(const User& user) {
    std::string sql = "UPDATE user SET password = ?, name = ?, user_type = ? WHERE email = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, user.getPassword().c_str(), user.getPassword().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, user.getName().c_str(), user.getName().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, user.getEmail().c_str(), user.getEmail().size(), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, user.getUserType().c_str(), user.getUserType().size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

/**
 * @brief Remove user from database
*/
bool UserDao::remove(const User& user) {
    std::string sql = "DELETE FROM user WHERE email = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, user.getEmail().c_str(), user.getEmail().size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

/**
 * @brief Find user by email
*/
User UserDao::findByEmail(const std::string& email) {
    std::string sql = "SELECT email, password, name, user_type FROM user WHERE email = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return User();
    }
    sqlite3_bind_text(stmt, 1, email.c_str(), email.size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return User();
    }
    std::string _email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    std::string userType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    sqlite3_finalize(stmt);
    return User(_email, password, name, userType);
}

/**
 * @brief Find all users
*/
std::vector<User> UserDao::findAll() {
    std::string sql = "SELECT email, password, name, user_type FROM user";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return std::vector<User>();
    }
    std::vector<User> users;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string userType = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        users.push_back(User(email, password, name, userType));
    }
    sqlite3_finalize(stmt);
    return users;
}

/**
 * @brief Verify user credentials
*/
bool UserDao::verify(const std::string& email, const std::string& hashPassword) {
    std::string sql = "SELECT email, password FROM user WHERE email = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, email.c_str(), email.size(), SQLITE_STATIC);
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db.getHandle()) << std::endl;
        return false;
    }
    std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    sqlite3_finalize(stmt);
    return password == hashPassword;
}
