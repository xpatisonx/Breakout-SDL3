//
// Created by bartek on 17.03.25.
//

#ifndef BREAKOUT_ENGINE_HPP
#define BREAKOUT_ENGINE_HPP

#include <SDL3/SDL.h>
#include <string>
#include <objects/ObjectContainer.hpp>
#include <memory>
#include <Level.hpp>
#include <GameStats.hpp>

class Engine
{
public:
    Engine();
    void run();
    bool init_sdl(std::string &message);
    bool init_level(std::size_t number);
    void main_loop();
    void render();
    void destroy();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    ObjectContainer object_container;
    std::array<std::unique_ptr<iLevel>, 1> levels;
    bool running;
    SDL_Event event;
    GameStats stats;
    

    void keyboard_event(const SDL_Event& event);
    void move();
    void collisions();
    void wait();
};

#endif //BREAKOUT_ENGINE_HPP
