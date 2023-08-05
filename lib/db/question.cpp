#include "question.hpp"
#include "../exception/exception.hpp"

Question::Question() {
    this->id = 0;
    this->question = "";
    this->answer = "";
    this->course_id = 0;
}

Question::Question(int id, std::string question, std::string answer, int course_id) {
    this->id = id;
    this->question = question;
    this->answer = answer;
    this->course_id = course_id;
}

Question::~Question() {}

int Question::get_id() {
    return this->id;
}

std::string Question::get_question() {
    return this->question;
}

std::string Question::get_answer() {
    return this->answer;
}

int Question::get_course_id() {
    return this->course_id;
}

void Question::set_id(int id) {
    this->id = id;
}

void Question::set_question(std::string question) {
    this->question = question;
}

void Question::set_answer(std::string answer) {
    this->answer = answer;
}

void Question::set_course_id(int course_id) {
    this->course_id = course_id;
}

bool Question::operator==(const Question& other) const {
    return this->id == other.id;
}

bool Question::operator!=(const Question& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Question& question) {
    os << "-----------------------------------------------------------" << std::endl;
    os << std::setw(20) << "Question ID: " << question.id << std::endl;
    os << std::setw(20) << "Question: " << question.question << std::endl;
    os << std::setw(20) << "Answer: " << question.answer << std::endl;
    os << std::setw(20) << "Course ID: " << question.course_id << std::endl;
    os << "-----------------------------------------------------------" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Question& question) {
    std::cout << "Question: ";
    is >> question.question;
    std::cout << "Answer: ";
    is >> question.answer;
    std::cout << "Course ID: ";
    is >> question.course_id;
    return is;
}

QuestionDao::QuestionDao(Database& db) {
    this->db = db;
}

QuestionDao::~QuestionDao() {}

void QuestionDao::add(Question& question) {
    std::string sql = "INSERT INTO question (question, answer, course_id) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_text(stmt, 1, question.get_question().c_str(), question.get_question().size(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, question.get_answer().c_str(), question.get_answer().size(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, question.get_course_id());
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

void QuestionDao::update(Question& question) {
    std::string sql = "UPDATE question SET question = ?, answer = ?, course_id = ? WHERE id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_text(stmt, 1, question.get_question().c_str(), question.get_question().size(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, question.get_answer().c_str(), question.get_answer().size(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, question.get_course_id());
    sqlite3_bind_int(stmt, 4, question.get_id());
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

void QuestionDao::remove(Question& question) {
    std::string sql = "DELETE FROM question WHERE id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, question.get_id());
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_finalize(stmt);
}

std::vector<Question> QuestionDao::get_all() {
    std::vector<Question> questions;
    std::string sql = "SELECT * FROM question";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Question question;
        question.set_id(sqlite3_column_int(stmt, 0));
        question.set_question(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
        question.set_answer(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))));
        question.set_course_id(sqlite3_column_int(stmt, 3));
        questions.push_back(question);
    }
    sqlite3_finalize(stmt);
    return questions;
}

std::vector<Question> QuestionDao::get_all_by_course_id(int course_id) {
    std::vector<Question> questions;
    std::string sql = "SELECT * FROM question WHERE course_id = ?";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db.getHandle(), sql.c_str(), sql.size(), &stmt, NULL) != SQLITE_OK) {
        throw DBException("SQL error: " + std::string(sqlite3_errmsg(db.getHandle())));
    }
    sqlite3_bind_int(stmt, 1, course_id);
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Question question;
        question.set_id(sqlite3_column_int(stmt, 0));
        question.set_question(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1))));
        question.set_answer(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))));
        question.set_course_id(sqlite3_column_int(stmt, 3));
        questions.push_back(question);
    }
    sqlite3_finalize(stmt);
    return questions;
}
