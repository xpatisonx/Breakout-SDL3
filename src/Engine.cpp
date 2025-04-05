//
// Created by bartek on 17.03.25.
//

#include <Engine.hpp>
#include <Base.hpp>
#include <iostream>

Engine::Engine() : object_container(), levels()
{
    std::string message;
    if (!init_sdl(message))
    {
        std::cerr << message << std::endl;
        return;
    }

    levels[0] = std::make_unique<Level1>();

    if (!init_level(0))
    {
        std::cerr << "Coult not initialize level." << std::endl;
        return;
    }
}

bool Engine::init_sdl(std::string &message)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        message = "SDL could not initialize! SDL_Error: " + std::string(SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        message = "Window could not be created! SDL_Error: " + std::string(SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Tworzymy renderer w SDL3 - brak flag, tylko nazwa
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        message = "Renderer could not be created! SDL_Error: " + std::string(SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    return true;
}

bool Engine::init_level(std::size_t number)
{
    levels[number]->load_level(object_container);
    return true;
}

void Engine::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    object_container.render_everything(renderer);
    SDL_RenderPresent(renderer);
}

void Engine::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //    TTF_CloseFont(font);
}

void Engine::keyboard_event(const SDL_Event &event)
{
    Paddle *player = object_container.get_player();

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.key == SDLK_LEFT)
        {
            player->set_move_direction(MoveDirection::left);
        } else if (event.key.key == SDLK_RIGHT)
        {
            player->set_move_direction(MoveDirection::right);
        }
    } else if (event.type == SDL_EVENT_KEY_UP)
    {
        if (event.key.key == SDLK_LEFT)
        {
            player->set_move_direction(MoveDirection::none);
        } else if (event.key.key == SDLK_RIGHT)
        {
            player->set_move_direction(MoveDirection::none);
        }
    }
}

void Engine::move()
{
    object_container.move_everything();
}

void Engine::collisions()
{
    object_container.check_collisions();
}

void Engine::wait()
{
    SDL_Delay(16); // ~60 FPS
}

void Engine::main_loop()
{
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            keyboard_event(event);
        }
        collisions();
        move();
        render();

        wait();
    }
}

void Engine::run()
{
    running = true;
    main_loop();
}
