//
// Created by bpolo on 05.04.2025.
//

#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <objects/GameObject.hpp>

class Paddle : public GameObject
{
public:
    Paddle(SDL_FRect rectangle, SDL_Color color, float speed);

    void set_move_direction(MoveDirection direction);
    void move() override;

private:
    MoveDirection move_direction;
};

#endif //PADDLE_HPP
