//
// Created by bartek on 16.03.25.
//

#ifndef BREAKOUT_GAMEOBJECT_HPP
#define BREAKOUT_GAMEOBJECT_HPP

#include <SDL3/SDL.h>
#include <objects/iGameObject.hpp>

constexpr float PADDLE_SPEED = 5.0f;
constexpr float BALL_SPEED_X = 4.0f;
constexpr float BALL_SPEED_Y = -4.0f;
constexpr float BONUS_SPEED = 4.0f;

class GameObject : public iGameObject
{
public:
    explicit GameObject(SDL_FRect rectangle, SDL_Color color, ObjectType type, Speed speed = {0, 0});

    void render(SDL_Renderer *renderer) override;
    void set_speed(Speed new_speed) override;
    void move() override;
    void check_collisions(ObjectContainerMap& objects_map) override;

    ObjectType get_type() override;

    SDL_FRect rect;
protected:
    SDL_Color color;
    Speed speed;
    ObjectType type;
};


#endif //BREAKOUT_GAMEOBJECT_HPP
