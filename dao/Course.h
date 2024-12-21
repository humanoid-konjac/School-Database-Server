#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course {
public:
    Course()=default;

    int getId() const { return id; }
    std::string getTime() const { return time; }
    std::string getLocation() const { return location; }
    std::string getName() const { return name; }
    std::string getTeacher() const { return teacher; }

    void setId(int id) { this->id = id; }
    void setTime(std::string time) { this->time = time; }
    void setLocation(std::string location) { this->location = location; }
    void setName(std::string name) { this->name = name; }
    void setTeacher(std::string teacher) { this->teacher = teacher; }

private:
    int id;
    std::string name, time, location, teacher;
};

#endif