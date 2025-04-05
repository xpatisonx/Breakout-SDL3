//
// Created by bpolo on 05.04.2025.
//

#include <objects/Ball.hpp>
#include <Base.hpp>
#include <cmath>

Ball::Ball(SDL_FRect rectangle, SDL_Color color, Speed speed) : GameObject(rectangle, color, ObjectType::ball, speed)
{
}

void Ball::check_collisions(ObjectContainerMap& objects_map)
{
    collision_with_walls();
    Paddle* paddle = dynamic_cast<Paddle *>(objects_map[ObjectType::paddle].at(0).get());
    collission_with_paddle(paddle);
    collission_with_bricks(objects_map[ObjectType::brick]);
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

void Ball::collission_with_paddle(Paddle* paddle)
{
    if (rect.y + rect.h >= paddle->rect.y &&
            rect.x + rect.w >= paddle->rect.x &&
            rect.x <= paddle->rect.x + paddle->rect.w)
    {
        float relativeIntersectX = (rect.x + rect.w / 2) - (paddle->rect.x + paddle->rect.w / 2);
        float normalizeIntersectX = relativeIntersectX / (paddle->rect.w / 2);

        // Kąt odbicia - im dalej od środka, tym bardziej na boki
        float angle = normalizeIntersectX * (M_PI / 3); // Maksymalnie 60 stopni
        float new_speed = sqrt(speed.vx * speed.vx + speed.vy * speed.vy);

        speed.vx = new_speed * sin(angle);
        speed.vy = -new_speed * cos(angle);
        rect.y = rect.y - rect.h;
    }
}

void Ball::collission_with_bricks(ObjectContainerVec& bricks)
{
}