#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
// #include <SDL3_ttf/SDL_ttf.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const float PADDLE_SPEED = 5.0f;
const float BALL_SPEED_X = 4.0f;
const float BALL_SPEED_Y = -4.0f;

const int BRICK_ROWS = 5;
const int BRICK_COLS = 10;
const float BRICK_WIDTH = 68;
const float BRICK_HEIGHT = 20;
const float BRICK_SPACING = 8;
const float BRICK_OFFSET_X = 25;
const float BRICK_OFFSET_Y = 50;

struct GameObject {
    SDL_FRect rect;  // SDL_FRect pozwala na bardziej precyzyjne pozycjonowanie
    SDL_Color color;
    float vx = 0, vy = 0; // Dodajemy prędkość

    void render(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    void move() {
        rect.x += vx;
        rect.y += vy;
    }
};

struct Brick {
    SDL_FRect rect;
    SDL_Color color;
    bool active = true; // Flaga, czy cegiełka nadal istnieje

    void render(SDL_Renderer* renderer) {
        if (active) {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
};

int main() {
    /////////////////////////////////////////
    ///   Inicjalizacja
    /////////////////////////////////////////

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Breakout", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Tworzymy renderer w SDL3 - brak flag, tylko nazwa
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /////////////////////////////////////////
    ///   Dodawanie obiektów
    /////////////////////////////////////////

    // Dodawanie obiektów gry
    GameObject paddle = {{350, 550, 100, 20}, {255, 255, 255, 255}};
    GameObject ball =  {{390, 530, 20, 20}, {255, 0, 0, 255}, BALL_SPEED_X, BALL_SPEED_Y};
    std::vector<Brick> bricks;
    for (int row = 0; row < BRICK_ROWS; ++row) {
        for (int col = 0; col < BRICK_COLS; ++col) {
            bricks.push_back({
                { BRICK_OFFSET_X + col * (BRICK_WIDTH + BRICK_SPACING),
                  BRICK_OFFSET_Y + row * (BRICK_HEIGHT + BRICK_SPACING),
                  BRICK_WIDTH, BRICK_HEIGHT },
                { 200, 200, 0, 255 } // Żółty kolor
            });
        }
    }

    /////////////////////////////////////////
    ///   Interface
    /////////////////////////////////////////
    int score = 0;
    // TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    // if (!font)
    // {
    //     std::cerr << "Failed to load font! SDL_Error: " << SDL_GetError() << std::endl;
    // }


    /////////////////////////////////////////
    ///   Sterowanie
    /////////////////////////////////////////

    bool running = true;
    bool moveLeft = false, moveRight = false;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_LEFT) {
                    moveLeft = true;
                } else if (event.key.key == SDLK_RIGHT) {
                    moveRight = true;
                }
            } else if (event.type == SDL_EVENT_KEY_UP) {
                if (event.key.key == SDLK_LEFT) {
                    moveLeft = false;
                } else if (event.key.key == SDLK_RIGHT) {
                    moveRight = false;
                }
            }
        }

        /////////////////////////////////////////
        ///   RUCH
        /////////////////////////////////////////

        // Ruch paletki
        if (moveLeft && paddle.rect.x > 0) {
            paddle.rect.x -= PADDLE_SPEED;
        }
        if (moveRight && paddle.rect.x + paddle.rect.w < SCREEN_WIDTH) {
            paddle.rect.x += PADDLE_SPEED;
        }

        // Ruch piłki
        ball.move();

        // Odbicie od ścian bocznych
        if (ball.rect.x <= 0 || ball.rect.x + ball.rect.w >= SCREEN_WIDTH) {
            ball.vx = -ball.vx;
        }

        // Odbicie od górnej ściany
        if (ball.rect.y <= 0) {
            ball.vy = -ball.vy;
        }

        /////////////////////////////////////////
        ///   Kolizje
        /////////////////////////////////////////

        // Kolizja z paletką
        if (ball.rect.y + ball.rect.h >= paddle.rect.y &&
            ball.rect.x + ball.rect.w >= paddle.rect.x &&
            ball.rect.x <= paddle.rect.x + paddle.rect.w) {

            ball.vy = -ball.vy; // Odbicie
            ball.rect.y = paddle.rect.y - ball.rect.h; // Uniknięcie zapadnięcia się w paletkę
            }

        // Kolizja z cegiełką
        for (auto& brick : bricks) {
            if (brick.active &&
                ball.rect.x < brick.rect.x + brick.rect.w &&
                ball.rect.x + ball.rect.w > brick.rect.x &&
                ball.rect.y < brick.rect.y + brick.rect.h &&
                ball.rect.y + ball.rect.h > brick.rect.y)
            {
                if (ball.rect.x + ball.rect.w - ball.vx <= brick.rect.x ||
                    ball.rect.x - ball.vx >= brick.rect.x + brick.rect.w) {
                    ball.vx = -ball.vx; // Odbicie boczne
                    } else {
                        ball.vy = -ball.vy; // Odbicie pionowe
                    }

                // Usuwamy cegiełkę
                brick.active = false; // Usuwamy cegiełkę
                // Przyspieszenie
                ball.vx *= 1.02f;
                ball.vy *= 1.02f;

                // Dodaj punkty
                score += 10;
                break; // Tylko jedna cegiełka na klatkę
            }
        }

        /////////////////////////////////////////
        ///   Koniec gry - jeśli piłka spadnie poniżej ekranu
        /////////////////////////////////////////
        if (ball.rect.y > SCREEN_HEIGHT) {
            std::cout << "Game Over! Resetting ball...\n";
            ball.rect.x = 390;
            ball.rect.y = 530;
            ball.vx = BALL_SPEED_X;
            ball.vy = BALL_SPEED_Y;
        }


        /////////////////////////////////////////
        ///   Renderowanie
        /////////////////////////////////////////

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        paddle.render(renderer);
        ball.render(renderer);
        for (auto& brick : bricks) {
            brick.render(renderer);
        }

        // std::string scoreText = "Score: " + std::to_string(score);
        // SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText.c_str(), 200, {255, 255, 255});
        // SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        // SDL_FRect scoreRect = {10, 10, static_cast<float>(surface->w), static_cast<float>(surface->h)};
        // SDL_RenderTexture(renderer, texture, NULL, &scoreRect);
        // SDL_DestroySurface(surface);
        // SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    // TTF_CloseFont(font);
    return 0;
}