//
// Created by william on 03/10/22.
//

#ifndef LD51_CLIENT_ORB_H
#define LD51_CLIENT_ORB_H

#include "Monster.h"

class Orb : public Monster {
    float timeSinceLastMovement = 0.0;
    float movementInterval = 100;

public:
    Orb(World &world, sf::Vector2i position);

    void tick(float delta) override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void drawDarkness(sf::RenderTarget& target) const override;

    void targetPlayerInRange() override;

    void moveTowardsPlayer() override;

    void findNewSpot() override;
};

#endif //LD51_CLIENT_ORB_H
