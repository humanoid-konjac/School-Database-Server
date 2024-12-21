#ifndef STUDENTSDAO_H
#define STUDENTSDAO_H

#include <vector>
#include <string>
#include "Student.h"

class StudentsDao {
public:
    StudentsDao(const std::string& filePath = ".\\dao\\students.csv");
    void getAllStudents(std::vector<Student>& vec);
    void addStudent(const Student& student);
    void updateStudent(const Student& student);
    void deleteStudent(int id);
    Student getStudentById(int id);

private:
    std::string filePath;
    std::vector<Student> students;
    void loadFromFile();
    void saveToFile();
};

#endif // STUDENTSDAO_H
