//
// Created by bartek on 22.03.25.
//

#include <Level.hpp>
#include <SDL3/SDL.h>

bool Level1::load_level(ObjectContainer &container)
{
    paddle = std::make_unique<Paddle>(
        Paddle{{350, 550, 100, 20}, {255, 255, 255, 255}, PADDLE_SPEED});
    container.add_object(std::move(paddle));

    ball = std::make_unique<Ball>(
        Ball{{390, 530, 20, 20}, {255, 0, 0, 255}, {BALL_SPEED_X, BALL_SPEED_Y}});
    container.add_object(std::move(ball));

    load_bricks(container);

    container.add_movable({ObjectType::paddle, ObjectType::ball, ObjectType::bonus});
    return true;
}

void Level1::load_bricks(ObjectContainer &container)
{
    for (int row = 0; row < BRICK_ROWS; ++row)
    {
        for (int col = 0; col < BRICK_COLS; ++col)
        {
            std::unique_ptr<GameObject> tmp_brick = std::make_unique<Brick>(
                Brick(SDL_FRect(BRICK_OFFSET_X + col * (BRICK_WIDTH + BRICK_SPACING),
                                BRICK_OFFSET_Y + row * (BRICK_HEIGHT + BRICK_SPACING),
                                BRICK_WIDTH,
                                BRICK_HEIGHT),
                      SDL_Color{200, 200, 0, 255}));
            container.add_object(std::move(tmp_brick));
        }
    }
}
