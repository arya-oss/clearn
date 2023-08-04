#ifndef _LIB_VIEW_ADMINVIEW_HPP
#define _LIB_VIEW_ADMINVIEW_HPP

#include <iostream>
#include <string>

#include "../db/user.hpp"
#include "../db/database.hpp"
#include "View.hpp"

class AdminView : public View {
public:
    AdminView(User* user, Database* db) : View(user, db) {
        this->userDao = new UserDao(*db);
    }
    ~AdminView() {}
    void show();
    void run();
private:
    UserDao* userDao;
    void addUser();
    void removeUser();
    void updateUser();
    void listUsers();
};


#endif // _LIB_VIEW_ADMINVIEW_HPP