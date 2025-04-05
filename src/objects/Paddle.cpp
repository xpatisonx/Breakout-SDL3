//
// Created by bpolo on 05.04.2025.
//

#include <objects/Paddle.hpp>
#include <Base.hpp>

Paddle::Paddle(SDL_FRect rectangle, SDL_Color color, float speed) : GameObject(
    rectangle, color, ObjectType::paddle, {speed, 0.0f})
{
}

void Paddle::set_move_direction(MoveDirection direction)
{
    move_direction = direction;
}

void Paddle::move()
{
    if (move_direction == MoveDirection::right and rect.x + rect.w < SCREEN_WIDTH)
    {
        rect.x += speed.vx;
    } else if (move_direction == MoveDirection::left and rect.x > 0)
    {
        rect.x -= speed.vx;
    }
}