//
// Created by bpolo on 05.04.2025.
//

#ifndef BALL_HPP
#define BALL_HPP

#include <objects/ObjectContainer.hpp>

class Ball : public GameObject
{
public:
    Ball(SDL_FRect rectangle, SDL_Color color, Speed speed = {0, 0});
    void check_collisions(ObjectContainerMap& objects_map) override;
private:
    void collision_with_walls();
    void collission_with_paddle(Paddle* paddle);
    void collission_with_bricks(ObjectContainerVec& bricks);
};

#endif //BALL_HPP
