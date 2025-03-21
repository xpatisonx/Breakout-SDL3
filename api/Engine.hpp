//
// Created by bartek on 17.03.25.
//

#ifndef BREAKOUT_ENGINE_HPP
#define BREAKOUT_ENGINE_HPP

#include <SDL3/SDL.h>
#include <string>
#include <GameObject.hpp>
#include <memory>
#include <map>
#include <vector>

using ObjectContainerType = std::map<ObjectType, std::vector<std::unique_ptr<iGameObject>>>; //todo: zrobić klasę opakowującą ten kontener;

class Engine
{
public:
    Engine();

    bool init_sdl(std::string &message);

    bool init_level();

private:
    ObjectContainerType object_container; //todo:
};

#endif //BREAKOUT_ENGINE_HPP
