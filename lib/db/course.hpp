#ifndef __LIB_DB_COURSE_HPP
#define __LIB_DB_COURSE_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "question.hpp"

class Course {
private:
    int id;
    std::string name;
    std::string description;
    int duration;
    float cost;
    std::string materials;
    std::vector<Question> questions;
public:
    Course();
    Course(int id, std::string name, std::string description, int duration, float cost, std::string materials);
    ~Course();

    int get_id();
    std::string get_name();
    std::string get_description();
    int get_duration();
    float get_cost();
    std::string get_materials();

    void set_id(int id);
    void set_name(std::string name);
    void set_description(std::string description);
    void set_duration(int duration);
    void set_cost(float cost);
    void set_materials(std::string materials);

    void add_question(Question question);
    std::vector<Question> get_questions();

    bool operator==(const Course& other) const;
    bool operator!=(const Course& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Course& course);
    friend std::istream& operator>>(std::istream& is, Course& course);
};

class CourseDao {
private:
    Database db;
public:
    CourseDao(Database& db);
    ~CourseDao();

    Course get(int id);
    std::vector<Course> get_all();
    void add(Course& course);
    void update(Course& course);
    void remove(int course_id);
};

#endif // __LIB_DB_COURSE_HPP