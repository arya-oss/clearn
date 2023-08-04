#include "AdminView.hpp"
#include <vector>

void AdminView::show() {
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Add user" << std::endl;
    std::cout << "2. Delete user" << std::endl;
    std::cout << "3. Update user" << std::endl;
    std::cout << "4. Display all users" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void AdminView::run() {
    bool exited = false;
    int option;
    while (!exited)
    {
        show();
        std::cin >> option;
        switch(option) {
        case 1:
            this->addUser();
            break;
        case 2:
            this->removeUser();
            break;
        case 3:
            this->updateUser();
            break;
        case 4:
            this->listUsers();
            break;
        case 5:
            exited = true;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
}

void AdminView::addUser() {
    User user;
    std::cin >> user;
    try {
        this->userDao->insert(user);
    } catch (UserAlreadyExistsException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::removeUser() {
    std::string email;
    std::cout << "Enter email: " << std::endl;
    std::cin >> email;
    try {
        this->userDao->remove(email);
    } catch (UserNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::listUsers() {
    try {
        std::vector<User> users = this->userDao->findAll();
        for (auto it = users.begin(); it != users.end(); it++) {
            std::cout << *it << std::endl;
        }
    } catch(DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::updateUser() {
    User user;
    std::cin >> user;
    try {
        this->userDao->update(user);
    } catch (UserNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}