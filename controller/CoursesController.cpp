#include "CoursesController.h"
#include "../framework/View.h"
#include <fstream>
#include <sstream>
#include <algorithm>

CoursesController::CoursesController() : coursesService() {}

std::string CoursesController::renderCoursesPage(const std::vector<Course>& courses) {
    std::string templateStr = View::render(".\\view\\courses.html");
    
    std::ostringstream courseRows;
    for (const auto& course : courses) {
        courseRows << "<tr><td><a href='/scorebycourse/" << course.getId() << "'>" << course.getId() << "</a></td>"
                    << "<td>" << course.getName() << "</td>"
                    << "<td>" << course.getTime() << "</td>"
                    << "<td>" << course.getLocation() << "</td>"
                    << "<td>" << course.getTeacher() << "</td></tr>\n";
    }

    templateStr = Util::replacePlaceholder(templateStr, "{{courses-arr}}", courseRows.str());
    
    return templateStr;
}

void CoursesController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    response.setContentType("text/html");

    std::vector<Course> courses;
    coursesService.getAllCourses(courses);
    response.setBody(renderCoursesPage(courses));
}