#ifndef _SCORE__H_
#define _SCORE__H_

#include <fstream>
#include <string>

class ScoreManager {
public:
    static void Init();
    static void SaveHighScore();
    static int GetScore();
    static int GetHighScore();
    static void UpdateScore(int y);
    static void Reset();

private:
    static int score;
    static int highScore;
    static const std::string savePath;
    static void Load();
};

#endif // _SCORE__H_
