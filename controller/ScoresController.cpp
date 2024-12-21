#include "ScoresController.h"

#include "../framework/View.h"
#include "../framework/util.h"

#include <fstream>
#include <sstream>
#include <algorithm>


// 查询某个学生的成绩 Controller

ScoresByStudentController::ScoresByStudentController() : scoresService(), coursesService(), studentsService() {}

std::string ScoresByStudentController::renderScoresPage(const Student& student, const std::vector<Score>& scores) {
    std::string templateStr = View::render(".\\view\\scores_by_stu.html");
    
    templateStr = Util::replacePlaceholder(templateStr, "{{id}}", std::to_string(student.getId()));
    templateStr = Util::replacePlaceholder(templateStr, "{{name}}", student.getName());
    templateStr = Util::replacePlaceholder(templateStr, "{{age}}", std::to_string(student.getAge()));
    templateStr = Util::replacePlaceholder(templateStr, "{{sex}}", student.getSex());

    std::ostringstream scoreRows;

    for (const auto& score : scores) {
        Course course(coursesService.getCourseById(score.getCourseId()));
        scoreRows << "<tr>"
                    << "<td><a href='/scorebycourse/" << course.getId() << "'>" << course.getId() << "</td>"
                    << "<td>" << course.getName() << "</td>"
                    << "<td>" << score.getScore() << "</td>"
                    << "<td>" << course.getTime() << "</td>"
                    << "<td>" << course.getLocation() << "</td>"
                    << "<td>" << course.getTeacher() << "</td></tr>\n";
    }

    templateStr = Util::replacePlaceholder(templateStr, "{{scores-arr}}", scoreRows.str());
    
    return templateStr;
}

void ScoresByStudentController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    response.setContentType("text/html");

    std::vector<Score> scores;
    int stu_id = Util::stringToInt(request.getHeader("stu_id"));
    scoresService.getScoresByStudentId(scores, stu_id);
    response.setBody(renderScoresPage(studentsService.getStudentById(stu_id), scores));
}

// 查询某门课程的成绩 Controller

ScoresByCourseController::ScoresByCourseController() : scoresService(), coursesService(), studentsService() {}

std::string ScoresByCourseController::renderScoresPage(const Course& course, const std::vector<Score>& scores, int scoreFrom, int scoreTo) {
    std::string templateStr = View::render(".\\view\\scores_by_course.html");
    
    templateStr = Util::replacePlaceholder(templateStr, "{{id}}", std::to_string(course.getId()));
    templateStr = Util::replacePlaceholder(templateStr, "{{name}}", course.getName());
    templateStr = Util::replacePlaceholder(templateStr, "{{time}}", course.getTime());
    templateStr = Util::replacePlaceholder(templateStr, "{{location}}", course.getLocation());
    templateStr = Util::replacePlaceholder(templateStr, "{{teacher}}", course.getTeacher());

    std::ostringstream scoreRows;

    for (const auto& score : scores) {
        if( (scoreFrom >= 0 ? score.getScore() < scoreFrom : false) || (scoreTo >= 0 ? score.getScore() > scoreTo : false)) continue;
        Student student(studentsService.getStudentById(score.getStudentId()));
        scoreRows << "<tr>"
                    << "<td><a href='/scorebystudent/" << student.getId() << "'>" << student.getId() << "</a></td>"
                    << "<td>" << student.getName() << "</td>"
                    << "<td>" << score.getScore() << "</td>"
                    << "<td>" << student.getAge() << "</td>"
                    << "<td>" << student.getSex() << "</td></tr>\n";
    }

    templateStr = Util::replacePlaceholder(templateStr, "{{scores-arr}}", scoreRows.str());
    templateStr = Util::replacePlaceholder(templateStr, "{{score-range}}", (scoreFrom < 0 && (scoreTo < 0 || scoreTo > 100)) ? "All" : (scoreFrom >= 0 ? std::to_string(scoreFrom) : "0") + "&nbsp;-&nbsp;" + ((scoreTo >= 0 && scoreTo <= 100) ? std::to_string(scoreTo) : "100"));
    
    return templateStr;
}

void ScoresByCourseController::handleRequest(const HttpRequest &request, HttpResponse &response) {
    response.setContentType("text/html");

    std::vector<Score> scores;

    int scoreFrom = Util::stringToInt(request.getHeader("scorefrom"));
    int scoreTo = Util::stringToInt(request.getHeader("scoreto"));

    int course_id = Util::stringToInt(request.getHeader("course_id"));
    scoresService.getScoresByCourseId(scores, course_id);
    response.setBody(renderScoresPage(coursesService.getCourseById(course_id), scores, scoreFrom, scoreTo));
}