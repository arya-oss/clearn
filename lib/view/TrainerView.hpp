#ifndef _LIB_VIEW_TRAINERVIEW_HPP
#define _LIB_VIEW_TRAINERVIEW_HPP

#include <iostream>
#include <string>
#include "View.hpp"

class TrainerView : public View {
public:
    TrainerView(User* user) : View(user) {}
    ~TrainerView() {}
    void show();
    void run();
};

#endif // _LIB_VIEW_TRAINEEVIEW_HPP