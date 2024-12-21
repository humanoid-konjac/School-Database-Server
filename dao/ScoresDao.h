#ifndef SCORESDAO_H
#define SCORESDAO_H

#include <vector>
#include <string>
#include "Score.h"

class ScoresDao {
public:
    ScoresDao(const std::string& filePath = ".\\dao\\scores.csv");
    void getAllScores(std::vector<Score>& vec);
    void addScore(const Score& score);

private:
    std::string filePath;
    std::vector<Score> scores;
    void loadFromFile();
    void saveToFile();
};

#endif
