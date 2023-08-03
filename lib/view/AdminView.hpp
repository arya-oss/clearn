#ifndef _LIB_VIEW_ADMINVIEW_HPP
#define _LIB_VIEW_ADMINVIEW_HPP

#include <iostream>
#include <string>
#include "View.hpp"

class AdminView : public View {
public:
    AdminView(User* user) : View(user) {}
    ~AdminView() {}
    void show() {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Add user" << std::endl;
        std::cout << "2. Delete user" << std::endl;
        std::cout << "3. Update user" << std::endl;
        std::cout << "4. Display all users" << std::endl;
        std::cout << "5. Exit" << std::endl;
    }
};


#endif // _LIB_VIEW_ADMINVIEW_HPP