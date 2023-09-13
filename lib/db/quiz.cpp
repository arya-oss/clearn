#include "quiz.hpp"
#include "../exception/exception.hpp"

Quiz::Quiz(std::string question, int rightAnswer, std::vector<std::string> choices, int courseId) {
    this->question = question;
    this->rightAnswer = rightAnswer;
    this->choices = choices;
    this->courseId = courseId;
}

Quiz::~Quiz() {}

int Quiz::getId() {
    return this->id;
}

std::string Quiz::getQuestion() {
    return this->question;
}

int Quiz::getRightAnswer() {
    return this->rightAnswer;
}

std::vector<std::string> Quiz::getChoices() {
    return this->choices;
}

int Quiz::getCourseId() {
    return this->courseId;
}

std::ostream& operator<<(std::ostream& os, const Quiz& quiz) {
    os << "Q: " << quiz.question << std::endl;
    for (int i = 0; i < quiz.choices.size(); i++) {
        os << i + 1 << ". " << quiz.choices[i] << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Quiz& quiz) {
    std::string question;
    int rightAnswer;
    std::vector<std::string> choices;

    std::cout << "Question: ";
    std::getline(is, question);
    std::cout << "Right answer: ";
    is >> rightAnswer;
    std::cout << "Choices: " << std::endl;
    std::string choice;
    std::getline(is, choice);
    while (choice != "") {
        choices.push_back(choice);
        std::getline(is, choice);
    }

    quiz.question = question;
    quiz.rightAnswer = rightAnswer;
    quiz.choices = choices;

    return is;
}

QuizDao::QuizDao(Database& db) {
    this->db = db;
}

QuizDao::~QuizDao() {}

void QuizDao::create(Quiz& quiz) {
    std::string sql = "INSERT INTO quiz (question, right_answer, course_id, choice1, choice2, choice3, choice4) VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_text(stmt, 1, quiz.getQuestion().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, quiz.getRightAnswer());
    sqlite3_bind_int(stmt, 3, quiz.getCourseId());

    std::vector<std::string> choices = quiz.getChoices();

    for (int i = 0; i < choices.size(); i++) {
        sqlite3_bind_text(stmt, i + 4, choices[i].c_str(), -1, SQLITE_TRANSIENT);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

void QuizDao::remove(int quizId) {
    std::string sql = "DELETE FROM quiz WHERE id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, quizId);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

Quiz QuizDao::getById(int quizId) {
    std::string sql = "SELECT * FROM quiz WHERE id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, quizId);
    if (sqlite3_step(stmt) != SQLITE_ROW) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    std::string question = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
    int rightAnswer = sqlite3_column_int(stmt, 2);
    int courseId = sqlite3_column_int(stmt, 3);
    std::vector<std::string> choices;
    for (int i = 0; i < 4; i++) {
        choices.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i + 4))));
    }
    sqlite3_finalize(stmt);
    return Quiz(question, rightAnswer, choices, courseId);
}

std::vector<Quiz> QuizDao::getAll(int course_id) {
    std::string sql = "SELECT * FROM quiz WHERE course_id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, course_id);
    std::vector<Quiz> quizzes;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string question = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        int rightAnswer = sqlite3_column_int(stmt, 2);
        int courseId = sqlite3_column_int(stmt, 3);
        std::vector<std::string> choices;
        for (int i = 0; i < 4; i++) {
            choices.push_back(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i + 4))));
        }
        quizzes.push_back(Quiz(question, rightAnswer, choices, courseId));
    }
    sqlite3_finalize(stmt);
    return quizzes;
}