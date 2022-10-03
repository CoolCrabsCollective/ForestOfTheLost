//
// Created by william on 03/10/22.
//

#ifndef LD51_CLIENT_ORB_H
#define LD51_CLIENT_ORB_H

#include "Monster.h"

class Orb : public Monster {
public:
    Orb(World &world, sf::Vector2i position);

    void tick(float delta) override;

    void targetPlayerInRange() override;

    void moveTowardsPlayer() override;

    void findNewSpot() override;
};

#endif //LD51_CLIENT_ORB_H
