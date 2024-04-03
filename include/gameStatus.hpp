#ifndef GAMESTATUS_HPP
#define GAMESTATUS_HPP

#define INITIAL_LIFE 3
#define INITIAL_SCORE 0
#define INITIAL_SCORE_RATIO 1

class GameStatus
{
private:
    int m_life;
    int m_score;
    int m_scoreRatio;

public:
    GameStatus() : m_life(INITIAL_LIFE), m_score(INITIAL_SCORE), m_scoreRatio(INITIAL_SCORE_RATIO) {}
    ~GameStatus() {}

    // Reset
    void resetScore() { m_score = INITIAL_SCORE; }
    void resetLife() { m_life = INITIAL_LIFE; }
    void resetGameStatus()
    {
        resetScore();
        resetLife();
    }
    // Increase score
    void increaseScore() { m_score += 10 * m_scoreRatio; }

    // Decrease life
    void decreaseLife() { m_life -= 1; }

    // Getters
    int getLife() { return m_life; }
    int getScore() { return m_score; }
};

#endif