//
// Created by bpolo on 05.04.2025.
//

#include <objects/Ball.hpp>
#include <objects/Brick.hpp>
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

    if (rect.y > SCREEN_HEIGHT and life > 0)
    {
        // std::cout << "Game Over! Resetting ball...\n";
        --life;

        if (life > 0)
        {
            rect.x = 390;
            rect.y = 530;
        }
        speed.vx = 0;
        speed.vy = 0;
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
    // Kolizja z cegiełką
    for (auto& object: bricks)
    {
        auto& brick = reinterpret_cast<brickPtr&>(object);
        if (brick->is_active() &&
            rect.x < brick->rect.x + brick->rect.w &&
            rect.x + rect.w > brick->rect.x &&
            rect.y < brick->rect.y + brick->rect.h &&
            rect.y + rect.h > brick->rect.y)
        {
            if (rect.x + rect.w - speed.vx <= brick->rect.x ||
                rect.x - speed.vx >= brick->rect.x + brick->rect.w)
            {
                speed.vx = -speed.vx; // Odbicie boczne
            }
            else
            {
                speed.vy = -speed.vy; // Odbicie pionowe
            }

            // Usuwamy cegiełkę
            brick->deactivate(); // Usuwamy cegiełkę
            // Przyspieszenie
            //speed.vx *= 1.02f;
            //speed.vy *= 1.02f;

            // Dodaj punkty
            //score += 10;

             //   if (rand() % 5 == 0)
             //   {
             //       bonuses.push_back({brick.rect, {0, 200, 200}, rand() % 3});
             //   }

            break; // Tylko jedna cegiełka na klatkę
            }
        }
}