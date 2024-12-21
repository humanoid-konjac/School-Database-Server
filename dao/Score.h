#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score {
public:
    Score()=default;

    int getStudentId() const { return stu_id; }
    int getCourseId() const { return course_id; }
    int getScore() const { return score; }

    void setStudentId(int id) { this->stu_id = id; }
    void setCourseId(int id) { this->course_id = id; }
    void setScore(int score) { this->score = score; }

private:
    int stu_id,course_id,score;
};

#endif // SCORE_H