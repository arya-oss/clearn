#ifndef __LIB_DB_COURSE_HPP
#define __LIB_DB_COURSE_HPP

#include <string>

class Course {
private:
    int id;
    std::string name;
    std::string description;
public:
    Course();
    Course(int id, std::string name, std::string description, int teacher_id);
    ~Course();

    int get_id();
    std::string get_name();
    std::string get_description();
    int get_teacher_id();

    void set_id(int id);
    void set_name(std::string name);
    void set_description(std::string description);
    void set_teacher_id(int teacher_id);
};

#endif // __LIB_DB_COURSE_HPP