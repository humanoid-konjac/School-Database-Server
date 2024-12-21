#ifndef COURSESSERVICE_H
#define COURSESSERVICE_H

#include <vector>
#include "../dao/CoursesDao.h"
#include "../dao/Course.h"

class CoursesService {
public:
    CoursesService();
    void getAllCourses(std::vector<Course>& vec);
    Course getCourseById(int id);
private:
    CoursesDao coursesDao;
};

#endif