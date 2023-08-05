#ifndef _LIB_DB_QUESTION_HPP
#define _LIB_DB_QUESTION_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "database.hpp"

class Question {
private:
    int id;
    std::string question;
    std::string answer;
    int course_id;
public:
    Question();
    Question(int id, std::string question, std::string answer, int course_id);
    ~Question();

    int get_id();
    std::string get_question();
    std::string get_answer();
    int get_course_id();

    void set_id(int id);
    void set_question(std::string question);
    void set_answer(std::string answer);
    void set_course_id(int course_id);

    bool operator==(const Question& other) const;
    bool operator!=(const Question& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Question& question);
    friend std::istream& operator>>(std::istream& is, Question& question);
};

class QuestionDao {
private:
    Database db;
public:
    QuestionDao(Database& db);
    ~QuestionDao();

    Question get(int id);
    std::vector<Question> get_all();
    std::vector<Question> get_all_by_course_id(int course_id);
    void add(Question& question);
    void update(Question& question);
    void remove(Question& question);
};

#endif  // _LIB_DB_QUESTION_HPP