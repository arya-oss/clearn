#include <vector>
#include "AdminView.hpp"

AdminView::AdminView(User* user, Database* db) : View(user, db) {
    this->userDao = new UserDao(*db);
    this->courseDao = new CourseDao(*db);
}

AdminView::~AdminView() {
    delete this->userDao;
    delete this->courseDao;
}

void AdminView::show() {
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Add user" << std::endl;
    std::cout << "2. Delete user" << std::endl;
    std::cout << "3. Update user" << std::endl;
    std::cout << "4. Display all users" << std::endl;
    std::cout << "5. Add Course" << std::endl;
    std::cout << "6. Delete Course" << std::endl;
    std::cout << "7. Update Course" << std::endl;
    std::cout << "8. Display all Courses" << std::endl;
    std::cout << "9. Exit" << std::endl;
}

void AdminView::run() {
    bool exited = false;
    int option;
    while (!exited)
    {
        show();
        std::cin >> option;
        switch(option) {
        case 1:
            this->addUser();
            break;
        case 2:
            this->removeUser();
            break;
        case 3:
            this->updateUser();
            break;
        case 4:
            this->listUsers();
            break;
        case 5:
            this->addCourse();
            break;
        case 6:
            this->removeCourse();
            break;
        case 7:
            this->updateCourse();
            break;
        case 8:
            this->listCourses();
            break;
        case 9:
            exited = true;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
        }
    }
}

void AdminView::addUser() {
    User user;
    std::cin >> user;
    try {
        this->userDao->insert(user);
    } catch (UserAlreadyExistsException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::removeUser() {
    std::string email;
    std::cout << "Enter email: " << std::endl;
    std::cin >> email;
    try {
        this->userDao->remove(email);
    } catch (UserNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::listUsers() {
    try {
        std::vector<User> users = this->userDao->findAll();
        for (auto it = users.begin(); it != users.end(); it++) {
            std::cout << *it << std::endl;
        }
    } catch(DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::updateUser() {
    User user;
    std::cin >> user;
    try {
        this->userDao->update(user);
    } catch (UserNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::addCourse() {
    Course course;
    std::cin >> course;
    try {
        this->courseDao->add(course);
    } catch (CourseAlreadyExistsException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::removeCourse() {
    int courseId;
    std::cout << "Enter course id: " << std::endl;
    std::cin >> courseId;
    try {
        this->courseDao->remove(courseId);
    } catch (CourseNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::listCourses() {
    try {
        std::vector<Course> courses = this->courseDao->get_all();
        for (auto it = courses.begin(); it != courses.end(); it++) {
            std::cout << *it << std::endl;
        }
    } catch(DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}

void AdminView::updateCourse() {
    Course course;
    std::cin >> course;
    try {
        this->courseDao->update(course);
    } catch (CourseNotFoundException& e) {
        std::cerr << e.what() << std::endl;
    } catch (DBException& e) {
        std::cerr << e.what() << std::endl;
    }
}