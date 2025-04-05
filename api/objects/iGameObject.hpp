//
// Created by bpolo on 05.04.2025.
//

#ifndef IGAMEOBJECT_HPP
#define IGAMEOBJECT_HPP

#include <SDL3/SDL.h>
#include <array>
#include <vector>
#include <memory>
#include <map>

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

enum class MoveDirection : int
{
    none = 0,
    left = 1,
    right = 2
};

class iGameObject;

using ObjectContainerPtr = std::unique_ptr<iGameObject>;
using ObjectContainerVec = std::vector<ObjectContainerPtr>;
using ObjectContainerMap = std::map<ObjectType, ObjectContainerVec>;

class iGameObject
{
public:
    virtual ~iGameObject() = default;

    virtual void render(SDL_Renderer *render) = 0;

    virtual void set_speed(Speed speed) = 0;

    virtual void move() = 0;

    virtual ObjectType get_type() = 0;

    virtual void check_collisions(ObjectContainerMap& objects_map) = 0;
};


#endif //IGAMEOBJECT_HPP
