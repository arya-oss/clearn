#ifndef _LIB_VIEW_TRAINEEVIEW_HPP
#define _LIB_VIEW_TRAINEEVIEW_HPP

#include <iostream>
#include <string>
#include "View.hpp"

class TraineeView : public View {
public:
    TraineeView(User* user) : View(user) {}
    ~TraineeView() {}
    void show();
    void run();
};


#endif // _LIB_VIEW_TRAINEEVIEW_HPP