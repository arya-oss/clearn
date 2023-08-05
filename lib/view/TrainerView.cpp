#include "TrainerView.hpp"

TrainerView::TrainerView(User* user, Database* db): View(user, db) {
}

TrainerView::~TrainerView() {
}

void TrainerView::show() {
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Register Course" << std::endl;
    std::cout << "2. View Course Description" << std::endl;
    std::cout << "3. Take Test" << std::endl;
    std::cout << "4. View Profile" << std::endl;
    std::cout << "5. Answer Queries" << std::endl;
    std::cout << "6. Highest Trainee Scores" << std::endl;
    std::cout << "7. View All Course Description" << std::endl;
    std::cout << "8. Exit" << std::endl;
}

void TrainerView::run() {
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
            std::cout << "View Course Description" << std::endl;
            break;
        case 3:
            std::cout << "Take Test" << std::endl;
            break;
        case 4:
            std::cout << "View Profile" << std::endl;
            break;
        case 5:
            std::cout << "Answer Queries" << std::endl;
            break;
        case 6:
            std::cout << "Highest Trainee Scores" << std::endl;
            break;
        case 7:
            std::cout << "View All Course Description" << std::endl;
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