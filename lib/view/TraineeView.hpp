#ifndef _LIB_VIEW_TRAINEEVIEW_HPP
#define _LIB_VIEW_TRAINEEVIEW_HPP

#include <iostream>
#include <iomanip>
#include <string>

#include "../db/user.hpp"
#include "../db/database.hpp"
#include "View.hpp"

class TraineeView : public View {
public:
    TraineeView(User* user, Database* db);
    ~TraineeView();
    void show();
    void run();
private:
    void viewProfile();
};


#endif // _LIB_VIEW_TRAINEEVIEW_HPP