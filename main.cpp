#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

#include "lib/db/database.hpp"
#include "lib/utils/hash.hpp"
#include "lib/db/user.hpp"
#include "lib/exception/exception.hpp"
#include "lib/view/AdminView.hpp"
#include "lib/view/TrainerView.hpp"
#include "lib/view/TraineeView.hpp"


class LMS {
private:
    Database db;
    View* view;
    void displayChoices();
    void initDatabaseSchema();
public:
    LMS(const Database& db);
    ~LMS();
    void setView(std::string userType, User& user);
    void run();
    void registerUser();
    void loginUser();
};


int main(int argc, char* const argv[]) {
    Database db;
    if (!db.open("test.db")) {
        std::cerr << "Error opening database" << std::endl;
        return 1;
    }
    LMS lms(db);
    lms.run();
    return 0;
}

LMS::LMS(const Database& db) : db(db) {
    initDatabaseSchema();
}

LMS::~LMS() {
    db.close();
}

void LMS::initDatabaseSchema() {
    db.exec("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT NOT NULL UNIQUE, password TEXT NOT NULL, name TEXT NOT NULL, user_type TEXT NOT NULL);");
    db.exec("CREATE TABLE IF NOT EXISTS course (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, description TEXT NOT NULL, duration INTEGER NOT NULL, cost REAL NOT NULL, materials TEXT NOT NULL);");
    db.exec("CREATE TABLE IF NOT EXISTS question (id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT NOT NULL, answer TEXT NOT NULL, course_id INTEGER NOT NULL, FOREIGN KEY(course_id) REFERENCES course(id));");
    db.exec("CREATE TABLE IF NOT EXISTS quiz (id INTEGER PRIMARY KEY AUTOINCREMENT, question TEXT NOT NULL, right_answer INTEGER NOT NULL, choice1 TEXT NOT NULL, choice2 TEXT NOT NULL, choice3 TEXT NOT NULL, choice4 TEXT NOT NULL, course_id INTEGER NOT NULL, FOREIGN KEY(course_id) REFERENCES course(id));");
    db.exec("CREATE TABLE IF NOT EXISTS trainee_course (id INTEGER PRIMARY KEY AUTOINCREMENT, trainee_id INTEGER NOT NULL, course_id INTEGER NOT NULL, FOREIGN KEY(trainee_id) REFERENCES user(id), FOREIGN KEY(course_id) REFERENCES course(id));");
    db.exec("CREATE TABLE IF NOT EXISTS trainer_course (id INTEGER PRIMARY KEY AUTOINCREMENT, trainer_id INTEGER NOT NULL, course_id INTEGER NOT NULL, FOREIGN KEY(trainer_id) REFERENCES user(id), FOREIGN KEY(course_id) REFERENCES course(id));");
    db.exec("CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER NOT NULL, course_id INTEGER NOT NULL, FOREIGN KEY(user_id) REFERENCES user(id), FOREIGN KEY(course_id) REFERENCES course(id));");
}

void LMS::displayChoices() {
    std::cout << "\n\nWelcome to Library Management System" << std::endl;
    std::cout << "Please choose an option:" << std::endl;
    std::cout << "1. Register" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
}

void LMS::run() {
    bool exited = false;
    int option;
    while(!exited) {
        displayChoices();
        std::cin >> option;
        switch(option) {
        case 1:
            std::cout << "Register" << std::endl;
            registerUser();
            break;
        case 2:
            std::cout << "Login" << std::endl;
            loginUser();
            break;
        case 3:
            exited = true;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
    std::cout << "Bye!" << std::endl;
}

void LMS::registerUser() {
    User user;
    std::cin >> user;
    UserDao userDao(db);
    try {
        userDao.insert(user);
    } catch (UserAlreadyExistsException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void LMS::loginUser() {
    std::string email, password;
    std::cout << "Enter email: ";
    std::cin >> email;
    char * pass = getpass("Enter password: ");
    password = sha256(pass);
    UserDao userDao(db);
    try {
        if (userDao.verify(email, password)) {
            std::cout << "Login successful!" << std::endl;
            User user = userDao.findByEmail(email);
            setView(user.getUserType(), user);
            view->run();
        } else {
            std::cout << "Login failed!" << std::endl;
        }
    } catch (UserNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void LMS::setView(std::string userType, User& user) {
    if (userType == "admin") {
        this->view = new AdminView(&user, &db);
    } else if (userType == "trainer") {
        this->view = new TrainerView(&user, &db);
    } else if (userType == "trainee") {
        this->view = new TraineeView(&user, &db);
    }
}