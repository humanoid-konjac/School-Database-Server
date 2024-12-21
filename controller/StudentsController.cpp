#include "StudentsController.h"
#include "../framework/View.h"
#include "../framework/util.h"
#include <fstream>
#include <sstream>
#include <algorithm>

StudentsController::StudentsController() : studentsService() {}

std::string StudentsController::renderStudentsPage(const std::vector<Student>& students, int ageFrom, int ageTo) {
    std::string templateStr = View::render(".\\view\\students.html");
    
    std::ostringstream studentRows;
    for (const auto& student : students) {
        studentRows << "<tr><td><a href='/scorebystudent/" << student.getId() << "'>" << student.getId() << "</a></td>"
                    << "<td>" << student.getName() << "</td>"
                    << "<td>" << student.getAge() << "</td>"
                    << "<td>" << student.getSex() << "</td></tr>\n";
    }

    templateStr = Util::replacePlaceholder(templateStr, "{{stu-arr}}", studentRows.str());
    templateStr = Util::replacePlaceholder(templateStr, "{{age-range}}", (ageFrom < 0 && ageTo < 0) ? "All" : (ageFrom == -1 ? "0" : std::to_string(ageFrom)) + "&nbsp;-&nbsp;" + (ageTo == -1 ? "Infinity" : std::to_string(ageTo)));
    
    return templateStr;
}

void StudentsController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    response.setContentType("text/html");

    std::vector<Student> students;
    int ageFrom = Util::stringToInt(request.getHeader("agefrom"));
    int ageTo = Util::stringToInt(request.getHeader("ageto"));
    studentsService.getStudentsByAgeRange(ageFrom, ageTo, students);
    response.setBody(renderStudentsPage(students, ageFrom, ageTo));
}
