#include "score.h"

int ScoreManager::score = 0;
int ScoreManager::highScore = 0;
const std::string ScoreManager::savePath = "highscore.txt";

void ScoreManager::Load() {
    std::ifstream in(savePath);
    if (in.is_open()) {
        in >> highScore;
        in.close();
    } else {
        highScore = 0;
    }
}

void ScoreManager::SaveHighScore() {
    std::ofstream out(savePath);
    if (out.is_open()) {
        out << highScore;
        out.close();
    }
}

void ScoreManager::Init() {
    Load();
}

void ScoreManager::UpdateScore(int playerY) {
    if (playerY < 500 && playerY < (500 - score * 10)) {
        score = (500 - playerY) / 10;
    }
    if (score > highScore) {
        highScore = score;
    }
}

int ScoreManager::GetScore() {
    return score;
}

int ScoreManager::GetHighScore() {
    return highScore;
}

void ScoreManager::Reset() {
    score = 0;
}


