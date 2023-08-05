#ifndef _LIB_VIEW_TRAINERVIEW_HPP
#define _LIB_VIEW_TRAINERVIEW_HPP

#include <iostream>
#include <string>

#include "../db/user.hpp"
#include "../db/database.hpp"
#include "View.hpp"

class TrainerView : public View {
public:
    TrainerView(User* user, Database* db);
    ~TrainerView();
    void show();
    void run();
};

#endif // _LIB_VIEW_TRAINEEVIEW_HPP