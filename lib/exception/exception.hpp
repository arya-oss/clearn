#ifndef __LIB_EXCEPTION_EXCEPTION_HPP
#define __LIB_EXCEPTION_EXCEPTION_HPP

#include <exception>
#include <string>


class UserNotFoundException : public std::exception {
    public:
        UserNotFoundException(const std::string& email);
        ~UserNotFoundException();
        const char* what() const noexcept override;
    private:
        std::string email;
};

class UserAlreadyExistsException : public std::exception {
    public:
        UserAlreadyExistsException(const std::string& email);
        ~UserAlreadyExistsException();
        const char* what() const noexcept override;
    private:
        std::string email;
};

class DBException : public std::exception {
    public:
        DBException(const std::string& message);
        ~DBException();
        const char* what() const noexcept override;
    private:
        std::string message;
};

#endif  // __LIB_EXCEPTION_EXCEPTION_HPP