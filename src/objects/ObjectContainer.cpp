//
// Created by bpolo on 05.04.2025.
//

#include <objects/ObjectContainer.hpp>

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
        for (auto &obj: vec)
        {
            obj->render(renderer);
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
            obj->check_collisions(container);
        }
    }
}

Paddle *ObjectContainer::get_player()
{
    return dynamic_cast<Paddle *>(container[ObjectType::paddle].at(0).get());
}