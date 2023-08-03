#ifndef _LIB_VIEW_ADMINVIEW_HPP
#define _LIB_VIEW_ADMINVIEW_HPP

#include <iostream>
#include <string>
#include "View.hpp"

class AdminView : public View {
public:
    AdminView(User* user) : View(user) {}
    ~AdminView() {}
    void show();
    void run();
};


#endif // _LIB_VIEW_ADMINVIEW_HPP