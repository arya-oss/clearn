#include "TraineeView.hpp"

TraineeView::TraineeView(User* user, Database* db) : View(user, db) {
}

TraineeView::~TraineeView() {
}

void TraineeView::show() {
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Register Course" << std::endl;
    std::cout << "2. View Course Materials" << std::endl;
    std::cout << "3. Take Test" << std::endl;
    std::cout << "4. View Profile" << std::endl;
    std::cout << "5. Ask Queries" << std::endl;
    std::cout << "6. Highest Scores" << std::endl;
    std::cout << "7. Test Details" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

void TraineeView::run() {
    bool exited = false;
    int option;
    while (!exited)
    {
        show();
        std::cin >> option;
        switch(option) {
        case 1:
            std::cout << "Register Course" << std::endl;
            break;
        case 2:
            std::cout << "View Course Materials" << std::endl;
            break;
        case 3:
            std::cout << "Take Test" << std::endl;
            break;
        case 4:
            viewProfile();
            break;
        case 5:
            std::cout << "Ask Queries" << std::endl;
            break;
        case 6:
            std::cout << "Highest Scores" << std::endl;
            break;
        case 7:
            std::cout << "Test Details" << std::endl;
            break;
        case 8:
            exited = true;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
}

void TraineeView::viewProfile() {
    std::cout << this->user << std::endl;
}