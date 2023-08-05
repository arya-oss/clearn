#include "course.hpp"
#include "../exception/exception.hpp"

Course::Course() {
    this->id = 0;
    this->name = "";
}

Course::Course(int id, std::string name, std::string description, int duration, float cost, std::string materials) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->duration = duration;
    this->cost = cost;
    this->materials = materials;
}

Course::~Course() {}

int Course::get_id() {
    return this->id;
}

std::string Course::get_name() {
    return this->name;
}

std::string Course::get_description() {
    return this->description;
}

int Course::get_duration() {
    return this->duration;
}

float Course::get_cost() {
    return this->cost;
}

std::string Course::get_materials() {
    return this->materials;
}

void Course::set_id(int id) {
    this->id = id;
}

void Course::set_name(std::string name) {
    this->name = name;
}

void Course::set_description(std::string description) {
    this->description = description;
}

void Course::set_duration(int duration) {
    this->duration = duration;
}

void Course::set_cost(float cost) {
    this->cost = cost;
}

void Course::set_materials(std::string materials) {
    this->materials = materials;
}

void Course::add_question(Question question) {
    this->questions.push_back(question);
}

std::vector<Question> Course::get_questions() {
    return this->questions;
}

bool Course::operator==(const Course& other) const {
    return this->id == other.id;
}

bool Course::operator!=(const Course& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << "-----------------------------------------------------------" << std::endl;
    os << std::setw(20) << "Course ID: " << course.id << std::endl;
    os << std::setw(20) << "Course Name: " << course.name << std::endl;
    os << std::setw(20) << "Course Description: " << course.description << std::endl;
    os << std::setw(20) << "Course Duration: " << course.duration << std::endl;
    os << std::setw(20) << "Course Cost: " << course.cost << std::endl;
    os << std::setw(20) << "Course Materials: " << course.materials << std::endl;
    os << "-----------------------------------------------------------" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Course& course) {
    std::cout << "Enter course name: ";
    is >> course.name;
    std::cout << "Enter course description: ";
    is >> course.description;
    std::cout << "Enter course duration: ";
    is >> course.duration;
    std::cout << "Enter course cost: ";
    is >> course.cost;
    std::cout << "Enter course materials: ";
    is >> course.materials;
    return is;
}

CourseDao::CourseDao(Database& db) {
    this->db = db;
}

CourseDao::~CourseDao() {}

void CourseDao::add(Course& course) {
    std::string sql = "INSERT INTO course (name, description, duration, cost, materials) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_text(stmt, 1, course.get_name().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, course.get_description().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, course.get_duration());
    sqlite3_bind_double(stmt, 4, course.get_cost());
    sqlite3_bind_text(stmt, 5, course.get_materials().c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

std::vector<Course> CourseDao::get_all() {
    std::vector<Course> courses;
    std::string sql = "SELECT * FROM course";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        int duration = sqlite3_column_int(stmt, 3);
        float cost = sqlite3_column_double(stmt, 4);
        std::string materials = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
        Course course(id, name, description, duration, cost, materials);
        courses.push_back(course);
    }
    sqlite3_finalize(stmt);
    return courses;
}

Course CourseDao::get(int id) {
    std::string sql = "SELECT * FROM course WHERE id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    std::string description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
    int duration = sqlite3_column_int(stmt, 3);
    float cost = sqlite3_column_double(stmt, 4);
    std::string materials = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
    Course course(id, name, description, duration, cost, materials);
    sqlite3_finalize(stmt);
    return course;
}

void CourseDao::update(Course& course) {
    std::string sql = "UPDATE course SET name = ?, description = ?, duration = ?, cost = ?, materials = ? WHERE name = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_text(stmt, 1, course.get_name().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, course.get_description().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, course.get_duration());
    sqlite3_bind_double(stmt, 4, course.get_cost());
    sqlite3_bind_text(stmt, 5, course.get_materials().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, course.get_name().c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

void CourseDao::remove(int course_id) {
    std::string sql = "DELETE FROM course WHERE id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, course_id);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}