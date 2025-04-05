//
// Created by bpolo on 05.04.2025.
//

#ifndef OBJECTCONTAINER_HPP
#define OBJECTCONTAINER_HPP

#include <objects/GameObject.hpp>
#include <objects/Paddle.hpp>
#include <objects/Ball.hpp>
#include <objects/Brick.hpp>
#include <objects/Bonus.hpp>

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

private:
    ObjectContainerMap container{};
    std::vector<ObjectType> movable{};
};

#endif //OBJECTCONTAINER_HPP
