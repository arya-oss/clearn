#ifndef _LIB_VIEW_ADMINVIEW_HPP
#define _LIB_VIEW_ADMINVIEW_HPP

#include <iostream>
#include <string>

#include "../db/user.hpp"
#include "../db/database.hpp"
#include "../db/course.hpp"
#include "../exception/exception.hpp"
#include "View.hpp"

class AdminView : public View {
public:
    AdminView(User* user, Database* db);
    ~AdminView();
    void show();
    void run();
private:
    UserDao* userDao;
    CourseDao* courseDao;
    void addUser();
    void removeUser();
    void updateUser();
    void listUsers();
    void addCourse();
    void removeCourse();
    void updateCourse();
    void listCourses();
};


#endif // _LIB_VIEW_ADMINVIEW_HPP