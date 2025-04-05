//
// Created by bpolo on 05.04.2025.
//

#include <objects/Bonus.hpp>

Bonus::Bonus(SDL_FRect rectangle) : bonus_type(static_cast<BonusType>(rand() % 2)),
                                    GameObject(rectangle, BonusColors[static_cast<int>(bonus_type)], ObjectType::bonus,
                                               {0, BONUS_SPEED})
{
}