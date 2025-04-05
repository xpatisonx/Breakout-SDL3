//
// Created by bartek on 16.03.25.
//

#include <objects/GameObject.hpp>
#include <Engine.hpp>

void GameObject::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void GameObject::move()
{
    rect.x += speed.vx;
    rect.y += speed.vy;
}

void GameObject::check_collisions(ObjectContainerMap& objects_map)
{
    // intentionally empty
}

GameObject::GameObject(SDL_FRect rectangle, SDL_Color color, ObjectType type, Speed speed) : rect(rectangle),
    color(color),
    type(type),
    speed(speed)
{
}

void GameObject::set_speed(Speed new_speed)
{
    speed = new_speed;
}

ObjectType GameObject::get_type()
{
    return type;
}