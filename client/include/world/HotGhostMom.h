//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_HOTGHOSTMOM_H
#define LD51_CLIENT_HOTGHOSTMOM_H

#include "Monster.h"

class HotGhostMom : public Monster {
    const int MIN_RANGE_TO_PLAYER = 3;
    const int MAX_RANGE_TO_PLAYER = 10;

    bool removedOtherHotGhostMoms = false;

public:
    explicit HotGhostMom(World &world, sf::Vector2i position);

    void tick(float delta);

    void targetPlayerInRange() override;

    void moveTowardsPlayer() override;

    void findNewSpot() override;

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void drawDarkness(sf::RenderTarget& target) const override;
};

#endif //LD51_CLIENT_HOTGHOSTMOM_H
