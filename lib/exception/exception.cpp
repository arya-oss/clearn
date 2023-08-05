#include "exception.hpp"

UserNotFoundException::UserNotFoundException(const std::string& email) : email(email) {
}

UserNotFoundException::~UserNotFoundException() {
}

const char* UserNotFoundException::what() const noexcept {
    return "User not found";
}

UserAlreadyExistsException::UserAlreadyExistsException(const std::string& email) : email(email) {
}

UserAlreadyExistsException::~UserAlreadyExistsException() {
}

const char* UserAlreadyExistsException::what() const noexcept {
    return "User already exists";
}

DBException::DBException(const std::string& message) : message(message) {
}

DBException::~DBException() {
}

const char* DBException::what() const noexcept {
    return message.c_str();
}

CourseNotFoundException::CourseNotFoundException(int id) : id(id) {
}

CourseNotFoundException::~CourseNotFoundException() {
}

const char* CourseNotFoundException::what() const noexcept {
    return "Course not found";
}

CourseAlreadyExistsException::CourseAlreadyExistsException(const std::string& name) : name(name) {
}

CourseAlreadyExistsException::~CourseAlreadyExistsException() {
}

const char* CourseAlreadyExistsException::what() const noexcept {
    return "Course already exists";
}