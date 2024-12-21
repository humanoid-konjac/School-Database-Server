#ifndef STUDENTSSERVICE_H
#define STUDENTSSERVICE_H

#include <vector>
#include "../dao/StudentsDao.h"
#include "../dao/Student.h"

#include "CoursesService.h"
#include "ScoresService.h"

class StudentsService {
public:
    StudentsService();
    void getAllStudents(std::vector<Student>& vec);
    Student getStudentById(int id);
    void getStudentsByAgeRange(int ageFrom, int ageTo,std::vector<Student>& vec);
private:
    StudentsDao studentsDao;

    ScoresService scoreService;
};

#endif