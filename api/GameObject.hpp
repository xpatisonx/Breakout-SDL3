//
// Created by bartek on 16.03.25.
//

#ifndef BREAKOUT_GAMEOBJECT_HPP
#define BREAKOUT_GAMEOBJECT_HPP

#include <SDL3/SDL.h>
#include <array>
#include <vector>
#include <memory>
#include <map>

constexpr float PADDLE_SPEED = 5.0f;
constexpr float BALL_SPEED_X = 4.0f;
constexpr float BALL_SPEED_Y = -4.0f;
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
    virtual void render(SDL_Renderer *render) = 0;

    virtual void set_speed(Speed speed) = 0;

    virtual void move() = 0;

    virtual ObjectType get_type() = 0;

    virtual void check_collisions() = 0;
};

class GameObject : public iGameObject
{
public:
    explicit GameObject(SDL_FRect rectangle, SDL_Color color, ObjectType type, Speed speed = {0, 0});

    void render(SDL_Renderer *renderer) override;
    void set_speed(Speed new_speed) override;
    void move() override;
    void check_collisions() override;

    ObjectType get_type() override;

protected:
    SDL_FRect rect;
    SDL_Color color;
    Speed speed;
    ObjectType type;
};

enum class MoveDirection : int
{
    none = 0,
    left = 1,
    right = 2
};


class Paddle : public GameObject
{
public:
    Paddle(SDL_FRect rectangle, SDL_Color color, float speed);

    void set_move_direction(MoveDirection direction);
    void move() override;

private:
    MoveDirection move_direction;
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

constexpr SDL_Color BonusColors[]{
    {0, 200, 200},
    {200, 0, 0}
};

class Ball : public GameObject
{
public:
    Ball(SDL_FRect rectangle, SDL_Color color, Speed speed = {0, 0});
    void check_collisions() override;
private:
    void collision_with_walls();
    void collission_with_paddle( paddle);
    void collission_with_bricks();
};

class Bonus : public GameObject
{
public:
    Bonus(SDL_FRect rectangle);

private:
    BonusType bonus_type;
};

using ObjectContainerPtr = std::unique_ptr<GameObject>;
using ObjectContainerVec = std::vector<ObjectContainerPtr>;
using ObjectContainerMap = std::map<ObjectType, ObjectContainerVec>;

class ObjectContainer
{
public:
    ObjectContainer();

    void add_object(std::unique_ptr<GameObject> object);
    void render_everything(SDL_Renderer *renderer);
    void move_everything();
    void add_movable(std::initializer_list<ObjectType> types);
    void check_collisions();

    Paddle *get_player();
    GameObject *get_ball();

private:
    ObjectContainerMap container{};
    std::vector<ObjectType> movable{};
};

#endif //BREAKOUT_GAMEOBJECT_HPP
