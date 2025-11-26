#ifndef GAMESTATS_HPP
#define GAMESTATS_HPP

#include <memory>

class GameStats
{
public:
    GameStats();
    GameStats(std::size_t lifes, std::size_t score);
    
    void increment_life();
    bool decrement_life();

    void modify_score(int delta_score);
private:
    std::size_t lifes;
    std::size_t score;
};

#endif