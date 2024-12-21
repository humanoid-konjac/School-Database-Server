#ifndef SCORESSERVICE_H
#define SCORESSERVICE_H

#include <vector>
#include "../dao/ScoresDao.h"
#include "../dao/Score.h"

class ScoresService {
public:
    ScoresService();
    void getAllScores(std::vector<Score>& vec);
    void getScoresByStudentId(std::vector<Score>& vec, int stu_id);
    void getScoresByCourseId(std::vector<Score>& vec, int course_id);
    int getScore(int stu_id, int course_id);
private:
    ScoresDao scoresDao;
};

#endif