//
// Created by bartek on 17.03.25.
//

#include <Engine.hpp>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Engine::Engine()
{
    std::string message;
    if (!init_sdl(message))
    {
        std::cerr << message << std::endl;
        return;
    }
    if (!init_level())
    {
        std::cerr << "Coult not initialize level." << std::endl;
        return;
    }
}

bool Engine::init_sdl(std::string& message)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        message = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
        return false;
    }

    SDL_Window *window = SDL_CreateWindow("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        message = "Window could not be created! SDL_Error: " + std::string(SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Tworzymy renderer w SDL3 - brak flag, tylko nazwa
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        message = "Renderer could not be created! SDL_Error: " + std::string(SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
}

bool Engine::init_level()
{

}
