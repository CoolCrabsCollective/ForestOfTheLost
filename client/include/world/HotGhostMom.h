//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_HOTGHOSTMOM_H
#define LD51_CLIENT_HOTGHOSTMOM_H

#include "Monster.h"

class HotGhostMom : public Monster {
    int MIN_RANGE_TO_PLAYER = 3;
    int MAX_RANGE_TO_PLAYER = 10;

public:
    explicit HotGhostMom(World &world, sf::Vector2i position);

    void tick(float delta) override;

    void targetPlayerInRange() override;

    void moveTowardsPlayer() override;
};

#endif //LD51_CLIENT_HOTGHOSTMOM_H
