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