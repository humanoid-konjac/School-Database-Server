#include "StudentsService.h"

StudentsService::StudentsService() : studentsDao(), scoreService() {}

void StudentsService::getAllStudents(std::vector<Student>& vec) {
    return studentsDao.getAllStudents(vec);
}

Student StudentsService::getStudentById(int id) {
    return studentsDao.getStudentById(id);
}

void StudentsService::getStudentsByAgeRange(int ageFrom, int ageTo,std::vector<Student>& vec) {
    vec.clear();
    std::vector<Student> temp;
    getAllStudents(temp);
    for(const auto& stu:temp)
    {
        if((ageFrom == -1 ? true : stu.getAge() >= ageFrom) && (ageTo == -1 ? true : stu.getAge() <= ageTo))
            vec.emplace_back(stu);
    }
}