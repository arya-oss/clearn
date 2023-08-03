#ifndef _LIB_VIEW_TRAINEEVIEW_HPP
#define _LIB_VIEW_TRAINEEVIEW_HPP

#include <iostream>
#include <string>
#include "View.hpp"

class TraineeView : public View {
public:
    TraineeView(User* user) : View(user) {}
    ~TraineeView() {}
    void show() {
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
};

#endif // _LIB_VIEW_TRAINEEVIEW_HPP