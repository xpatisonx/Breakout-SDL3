//
// Created by bartek on 16.03.25.
//

#ifndef BREAKOUT_GAMEOBJECT_HPP
#define BREAKOUT_GAMEOBJECT_HPP

#include <SDL3/SDL.h>
#include <array>

constexpr float PADDLE_SPEED = 5.0f;
constexpr float BALL_SPEED_X = 4.0f;
constexpr float BALL_SPEED_Y = 4.0f;
constexpr float BONUS_SPEED = 4.0f;

struct Speed
{
    float vx = 0, vy = 0; // Dodajemy prędkość
};

enum class ObjectType : int
{
    none = 0,
    paddle,
    ball,
    brick,
    bonus
};

class iGameObject
{
public:
    virtual void render(SDL_Renderer *render);
    virtual void set_speed(Speed speed);
    virtual void move();
};

class GameObject : public iGameObject
{
public:
    GameObject(SDL_FRect rectangle, SDL_Color color, ObjectType type, Speed speed);

    void render(SDL_Renderer *renderer) override;

    void set_speed(Speed new_speed) override;

    void move() override;

private:
    SDL_FRect rect;
    SDL_Color color;
    Speed speed;
    ObjectType type;
};

class Brick : public GameObject
{
public:
    Brick(SDL_FRect rectangle, SDL_Color color);
    void render(SDL_Renderer *renderer) override;
private:
    bool active;
};

enum class BonusType : int
{
    extension = 0,
    narrowing
};

constexpr SDL_Color BonusColors[]{{0,   200, 200},
                                  {200, 0,   0}};

class Bonus : public GameObject
{
public:
    Bonus(SDL_FRect rectangle);
private:
    BonusType bonus_type;
};

#endif //BREAKOUT_GAMEOBJECT_HPP
