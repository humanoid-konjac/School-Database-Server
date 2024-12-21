#ifndef COURSESDAO_H
#define COURSESDAO_H

#include <vector>
#include <string>
#include "Course.h"

class CoursesDao {
public:
    CoursesDao(const std::string& filePath = ".\\dao\\courses.csv");
    void getAllCourses(std::vector<Course>& vec);
    void addCourse(const Course& course);
    void updateCourse(const Course& course);
    void deleteCourse(int id);
    Course getCourseById(int id);

private:
    std::string filePath;
    std::vector<Course> courses;
    void loadFromFile();
    void saveToFile();
};

#endif