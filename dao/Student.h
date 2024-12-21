#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student()=default;

    int getId() const { return id; }
    int getAge() const { return age; }
    std::string getSex() const { return sex; }
    std::string getName() const { return name; }

    void setId(int id) { this->id = id; }
    void setAge(int age) { this->age = age; }
    void setSex(std::string sex) { this->sex = sex; }
    void setName(const std::string& name) { this->name = name; }

private:
    int id;
    std::string name;
    int age;
    std::string sex;
};

#endif // STUDENT_H
