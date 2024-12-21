#include "ScoresDao.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>

ScoresDao::ScoresDao(const std::string& filePath) : filePath(filePath) {
    loadFromFile();
}

void ScoresDao::getAllScores(std::vector<Score>& vec) {
    vec = scores;
}

void ScoresDao::addScore(const Score& score) {
    scores.push_back(score);
    saveToFile();
}

void ScoresDao::loadFromFile() {
    std::ifstream file(filePath);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        Score score;
        std::string item;
        std::stringstream ss(line);

        std::getline(ss, item, ',');
        score.setStudentId(std::stoi(item));

        std::getline(ss, item, ',');
        score.setCourseId(std::stoi(item));

        std::getline(ss, item, ',');
        score.setScore(std::stoi(item));

        scores.emplace_back(score);
    }
}

void ScoresDao::saveToFile() {
    // std::ofstream file(filePath);
    // for (const auto& score : scores) {
    //     file << score.getId() << " " << score.getName() << "\n";
    // }
}
