#include "ScoresService.h"

ScoresService::ScoresService() : scoresDao() {}

void ScoresService::getAllScores(std::vector<Score>& vec) {
    return scoresDao.getAllScores(vec);
}

void ScoresService::getScoresByStudentId(std::vector<Score>& vec, int stu_id) {
    vec.clear();
    std::vector<Score> temp;
    getAllScores(temp);
    for(auto& score:temp)
    {
        if(score.getStudentId() == stu_id)
            vec.emplace_back(score);
    }
}

void ScoresService::getScoresByCourseId(std::vector<Score>& vec, int course_id) {
    vec.clear();
    std::vector<Score> temp;
    getAllScores(temp);
    for(auto& score:temp)
    {
        if(score.getCourseId() == course_id)
            vec.emplace_back(score);
    }
}


int ScoresService::getScore(int stu_id, int course_id) {
    std::vector<Score> temp;
    getAllScores(temp);
    for(auto& score:temp)
    {
        if(score.getCourseId() == course_id && score.getStudentId() == stu_id)
            return score.getScore();
    }
    return -1;
}