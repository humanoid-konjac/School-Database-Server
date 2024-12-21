#include "StudentsDao.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

StudentsDao::StudentsDao(const std::string& filePath) : filePath(filePath) {
    loadFromFile();
}

void StudentsDao::getAllStudents(std::vector<Student>& vec) {
    vec = students;
}

Student StudentsDao::getStudentById(int id) {
    for (const auto& student : students) {
        if (student.getId() == id) {
            return student;
        }
    }
    throw std::runtime_error("Student not found");
}

void StudentsDao::addStudent(const Student& student) {
    students.push_back(student);
    saveToFile();
}

void StudentsDao::updateStudent(const Student& student) {
    for (auto& s : students) {
        if (s.getId() == student.getId()) {
            s = student;
            saveToFile();
            return;
        }
    }
    throw std::runtime_error("Student not found");
}

void StudentsDao::deleteStudent(int id) {
    students.erase(std::remove_if(students.begin(), students.end(), [id](const Student& s) {
        return s.getId() == id;
    }), students.end());
    saveToFile();
}

void StudentsDao::loadFromFile() {
    std::ifstream file(filePath);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        Student student;
        std::string item;
        std::stringstream ss(line);

        std::getline(ss, item, ',');
        student.setId(std::stoi(item));

        std::getline(ss, item, ',');
        student.setName(item);

        std::getline(ss, item, ',');
        student.setAge(std::stoi(item));

        std::getline(ss, item, ',');
        student.setSex(item);

        students.emplace_back(student);
    }
}

void StudentsDao::saveToFile() {
    std::ofstream file(filePath);
    for (const auto& student : students) {
        file << student.getId() << " " << student.getName() << "\n";
    }
}
