#ifndef _LIB_DB_QUIZ_HPP
#define _LIB_DB_QUIZ_HPP

#include <string>
#include <iostream>
#include <vector>

#include "../db/database.hpp"

class Quiz {
private:
    int id;
    std::string question;
    int rightAnswer;
    std::vector<std::string> choices;
    int courseId;
public:
    Quiz(std::string question, int rightAnswer, std::vector<std::string> choices, int courseId);
    ~Quiz();

    int getId();
    std::string getQuestion();
    int getRightAnswer();
    std::vector<std::string> getChoices();
    int getCourseId();

    friend std::ostream& operator<<(std::ostream& os, const Quiz& quiz);
    friend std::istream& operator>>(std::istream& is, Quiz& quiz);
};

class QuizDao {
protected:
    Database db;
public:
    QuizDao(Database& db);
    ~QuizDao();

    void create(Quiz& quiz);
    void remove(int quizId);
    Quiz getById(int quizId);
    std::vector<Quiz> getAll(int course_id);
};

#endif // _LIB_DB_QUIZ_HPP