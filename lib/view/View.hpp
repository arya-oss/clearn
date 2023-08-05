#ifndef _LIB_VIEW_VIEW_HPP
#define _LIB_VIEW_VIEW_HPP

#include "../db/database.hpp"
#include "../db/user.hpp"

class View {
public:
    View(User* user, Database* db) : user(user), db(db) {}
    virtual ~View() {}
    virtual void show() = 0;
    virtual void run() = 0;
protected:
    Database* db = nullptr;
    User* user = nullptr;
};

#endif // _LIB_VIEW_VIEW_HPP