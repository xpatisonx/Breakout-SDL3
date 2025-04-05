//
// Created by bpolo on 05.04.2025.
//

#ifndef BRICK_HPP
#define BRICK_HPP

#include<objects/GameObject.hpp>

class Brick : public GameObject
{
public:
    Brick(SDL_FRect rectangle, SDL_Color color);

    void render(SDL_Renderer *renderer) override;

private:
    bool active;
};

#endif //BRICK_HPP
