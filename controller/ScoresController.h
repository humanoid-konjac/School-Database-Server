#ifndef SCORESCONTROLLER_H
#define SCORESCONTROLLER_H

#include "../service/ScoresService.h"
#include "../service/CoursesService.h"
#include "../service/StudentsService.h"

#include "../service/ScoresService.h"

#include "../framework/Router.h"
#include "../framework/http.h"
#include "../framework/util.h"

#include <cctype>

class ScoresByStudentController: public Controller {
public:
    ScoresByStudentController();
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;

private:
    ScoresService scoresService;
    CoursesService coursesService;
    StudentsService studentsService;

    std::string renderScoresPage(const Student& student, const std::vector<Score>& scores);
};

class ScoresByCourseController: public Controller {
public:
    ScoresByCourseController();
    void handleRequest(const HttpRequest &request, HttpResponse &response) override;

private:
    ScoresService scoresService;
    CoursesService coursesService;
    StudentsService studentsService;

    std::string renderScoresPage(const Course& course, const std::vector<Score>& scores, int scoreFrom, int scoreTo);
};

#endif