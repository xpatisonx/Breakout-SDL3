//
// Created by bpolo on 05.04.2025.
//

#include <objects/Brick.hpp>

Brick::Brick(SDL_FRect rectangle, SDL_Color color) : GameObject(rectangle, color, ObjectType::brick),
                                                     active{true}
{
}

void Brick::render(SDL_Renderer *renderer)
{
    if (!active) return;
    GameObject::render(renderer);
}

bool Brick::is_active()
{
    return active;
}

void Brick::deactivate()
{
    active = false;
}
