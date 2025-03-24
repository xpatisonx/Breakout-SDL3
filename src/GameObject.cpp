//
// Created by bartek on 16.03.25.
//

#include <GameObject.hpp>
#include <cmath>

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

GameObject::GameObject(SDL_FRect rectangle, SDL_Color color, ObjectType type, Speed speed) :
        rect(rectangle),
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

void Brick::render(SDL_Renderer *renderer)
{
    if (!active) return;
    GameObject::render(renderer);
}

Brick::Brick(SDL_FRect rectangle, SDL_Color color) :
        GameObject(rectangle, color, ObjectType::brick),
        active{true}
{
}

Bonus::Bonus(SDL_FRect rectangle) :
    bonus_type(static_cast<BonusType>(rand() % 2)),
    GameObject(rectangle, BonusColors[static_cast<int>(bonus_type)], ObjectType::bonus, {0,BONUS_SPEED})
{
}

void ObjectContainer::add_object(std::unique_ptr<GameObject> object)
{
    container[object->get_type()].push_back(std::move(object));
}

void ObjectContainer::render_everything(SDL_Renderer *renderer)
{
    for (auto& [key, vec] : container) {  // Iteracja po mapie
        for (auto& obj : vec) {       // Iteracja po wektorze
            obj->render(renderer);       // Operacja na obiekcie
        }
    }
}

ObjectContainer::ObjectContainer() : container()
{

}
