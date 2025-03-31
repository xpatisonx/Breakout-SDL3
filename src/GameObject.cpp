//
// Created by bartek on 16.03.25.
//

#include <GameObject.hpp>
#include <cmath>
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

void GameObject::check_collisions()
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

void Brick::render(SDL_Renderer *renderer)
{
    if (!active) return;
    GameObject::render(renderer);
}

Ball::Ball(SDL_FRect rectangle, SDL_Color color, Speed speed) : GameObject(rectangle, color, ObjectType::ball, speed)
{
}

void Ball::check_collisions()
{
    collision_with_walls();
    collission_with_paddle();
    collission_with_bricks();
}

void Ball::collision_with_walls()
{
    // Odbicie od ścian bocznych
    if (rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH)
    {
        speed.vx = -speed.vx;
    }

    // Odbicie od górnej ściany
    if (rect.y <= 0)
    {
        speed.vy = -speed.vy;
    }
}

void Ball::collission_with_paddle()
{
    if (rect.y + rect.h >= paddle.rect.y &&
            rect.x + rect.w >= paddle.rect.x &&
            rect.x <= paddle.rect.x + paddle.rect.w)
    {
        float relativeIntersectX = (rect.x + rect.w / 2) - (paddle.rect.x + paddle.rect.w / 2);
        float normalizeIntersectX = relativeIntersectX / (paddle.rect.w / 2);

        // Kąt odbicia - im dalej od środka, tym bardziej na boki
        float angle = normalizeIntersectX * (M_PI / 3); // Maksymalnie 60 stopni
        float new_speed = sqrt(speed.vx * speed.vx + speed.vy * speed.vy);

        speed.vx = new_speed * sin(angle);
        speed.vy = -new_speed * cos(angle);
        rect.y = rect.y - rect.h;
    }
}

void Ball::collission_with_bricks()
{
}

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

Brick::Brick(SDL_FRect rectangle, SDL_Color color) : GameObject(rectangle, color, ObjectType::brick),
                                                     active{true}
{
}

Bonus::Bonus(SDL_FRect rectangle) : bonus_type(static_cast<BonusType>(rand() % 2)),
                                    GameObject(rectangle, BonusColors[static_cast<int>(bonus_type)], ObjectType::bonus,
                                               {0, BONUS_SPEED})
{
}

ObjectContainer::ObjectContainer()
{
}

void ObjectContainer::add_object(std::unique_ptr<GameObject> object)
{
    container[object->get_type()].push_back(std::move(object));
}

void ObjectContainer::render_everything(SDL_Renderer *renderer)
{
    for (auto &[key, vec]: container)
    {
        // Iteracja po mapie
        for (auto &obj: vec)
        {
            // Iteracja po wektorze
            obj->render(renderer); // Operacja na obiekcie
        }
    }
}

void ObjectContainer::move_everything()
{
    for (auto obj_type: movable)
    {
        ObjectContainerVec &obj_vec = container[obj_type];
        for (auto &obj: obj_vec)
        {
            obj->move();
        }
    }
}

void ObjectContainer::add_movable(std::initializer_list<ObjectType> types)
{
    movable.insert(movable.end(), types.begin(), types.end());
}

void ObjectContainer::check_collisions()
{
    for (auto &[key, vec]: container)
    {
        for (auto &obj: vec)
        {
            obj->check_collisions();
        }
    }
}

Paddle *ObjectContainer::get_player()
{
    return dynamic_cast<Paddle *>(container[ObjectType::paddle].at(0).get());
}

GameObject *ObjectContainer::get_ball()
{
    return container[ObjectType::ball].at(1).get();
}
