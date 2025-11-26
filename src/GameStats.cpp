#include <GameStats.hpp>

GameStats::GameStats() : lifes(0), score(0)
{
}

GameStats::GameStats(std::size_t lifes, std::size_t score) : lifes(lifes), score(score)
{
}

void GameStats::increment_life()
{
    ++lifes;
}

bool GameStats::decrement_life()
{
    return --lifes > 0;
}

void GameStats::modify_score(int delta_score)
{
    score += delta_score;
}
