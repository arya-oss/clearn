#ifndef _LIB_VIEW_VIEW_HPP
#define _LIB_VIEW_VIEW_HPP

#include "../db/user.hpp"

class View {
private:
    User* user = nullptr;
public:
    View(User* user) : user(user) {}
    virtual ~View() {}
    virtual void show() = 0;
    virtual void run() = 0;
};

#endif // _LIB_VIEW_VIEW_HPP