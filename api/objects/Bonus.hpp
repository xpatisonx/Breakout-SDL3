//
// Created by bpolo on 05.04.2025.
//

#ifndef BONUS_HPP
#define BONUS_HPP

#include <objects/GameObject.hpp>

enum class BonusType : int
{
    extension = 0,
    narrowing
};

constexpr SDL_Color BonusColors[]{
    {0, 200, 200},
    {200, 0, 0}
};

class Bonus : public GameObject
{
public:
    Bonus(SDL_FRect rectangle);

private:
    BonusType bonus_type;
};


#endif //BONUS_HPP
