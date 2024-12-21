#ifndef COURSESCONTROLLER_H
#define COURSESCONTROLLER_H

#include "../service/CoursesService.h"
#include "../framework/Router.h"
#include "../framework/http.h"
#include "../framework/util.h"

#include <cctype>

class CoursesController: public Controller {
public:
    CoursesController();
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;

private:
    CoursesService coursesService;
    std::string renderCoursesPage(const std::vector<Course>& courses);
};

#endif