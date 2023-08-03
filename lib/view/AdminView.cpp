#include "AdminView.hpp"

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
            std::cout << "Add user" << std::endl;
            break;
        case 2:
            std::cout << "Delete user" << std::endl;
            break;
        case 3:
            std::cout << "Update user" << std::endl;
            break;
        case 4:
            std::cout << "Display all users" << std::endl;
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