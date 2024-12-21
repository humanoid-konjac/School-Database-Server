#include "CoursesDao.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

CoursesDao::CoursesDao(const std::string& filePath) : filePath(filePath) {
    loadFromFile();
}

void CoursesDao::getAllCourses(std::vector<Course>& vec) {
    vec = courses;
}

Course CoursesDao::getCourseById(int id) {
    for (const auto& course : courses) {
        if (course.getId() == id) {
            return course;
        }
    }
    throw std::runtime_error("Course not found");
}

void CoursesDao::addCourse(const Course& course) {
    courses.push_back(course);
    saveToFile();
}

void CoursesDao::updateCourse(const Course& course) {
    for (auto& s : courses) {
        if (s.getId() == course.getId()) {
            s = course;
            saveToFile();
            return;
        }
    }
    throw std::runtime_error("Course not found");
}

void CoursesDao::deleteCourse(int id) {
    courses.erase(std::remove_if(courses.begin(), courses.end(), [id](const Course& s) {
        return s.getId() == id;
    }), courses.end());
    saveToFile();
}

void CoursesDao::loadFromFile() {
    std::ifstream file(filePath);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        Course course;
        std::string item;
        std::stringstream ss(line);

        std::getline(ss, item, ',');
        course.setId(std::stoi(item));

        std::getline(ss, item, ',');
        course.setName(item);

        std::getline(ss, item, ',');
        course.setTime(item);

        std::getline(ss, item, ',');
        course.setLocation(item);

        std::getline(ss, item, ',');
        course.setTeacher(item);

        courses.emplace_back(course);
    }
}

void CoursesDao::saveToFile() {
    std::ofstream file(filePath);
    for (const auto& course : courses) {
        file << course.getId() << " " << course.getName() << "\n";
    }
}
