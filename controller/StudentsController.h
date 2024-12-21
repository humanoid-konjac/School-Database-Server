#ifndef STUDENTSCONTROLLER_H
#define STUDENTSCONTROLLER_H

#include "../service/StudentsService.h"
#include "../framework/Router.h"
#include "../framework/http.h"

#include <cctype>

class StudentsController: public Controller {
public:
    StudentsController();
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;

private:
    StudentsService studentsService;
    std::string renderStudentsPage(const std::vector<Student>& students, int ageFrom, int ageTo);
};

#endif