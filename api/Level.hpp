//
// Created by bartek on 22.03.25.
//

#ifndef BREAKOUT_ILEVEL_HPP
#define BREAKOUT_ILEVEL_HPP

#include <objects/ObjectContainer.hpp>

class iLevel
{
public:
    virtual bool load_level(ObjectContainer &container) = 0;
};

class Level1 : public iLevel
{
public:
    Level1() = default;
    bool load_level(ObjectContainer &container) override;

private:
    const int BRICK_ROWS = 5;
    const int BRICK_COLS = 10;
    const float BRICK_WIDTH = 68;
    const float BRICK_HEIGHT = 20;
    const float BRICK_SPACING = 8;
    const float BRICK_OFFSET_X = 25;
    const float BRICK_OFFSET_Y = 50;

    std::unique_ptr<GameObject> paddle;
    std::unique_ptr<GameObject> ball;
    void load_bricks(ObjectContainer &container);
};

#endif //BREAKOUT_ILEVEL_HPP
