#include "CoursesService.h"

CoursesService::CoursesService() : coursesDao() {}

void CoursesService::getAllCourses(std::vector<Course>& vec) {
    return coursesDao.getAllCourses(vec);
}

Course CoursesService::getCourseById(int id) {
    return coursesDao.getCourseById(id);
}