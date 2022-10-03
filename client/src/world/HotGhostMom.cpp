//
// Created by william on 02/10/22.
//

#include "world/HotGhostMom.h"
#include <GameAssets.h>

HotGhostMom::HotGhostMom(World &world, sf::Vector2i position) : Monster(world, position,
                                                            world.getAssets().get(GameAssets::HOT_GHOST_MOM),
                                                            world.getAssets().get(GameAssets::SPOOKY_EYES)){
    attackMessage = "How TF did you get killed by the ghost mom?!?!? lmao skill issue.";
    scale = 2;
}

void HotGhostMom::tick(float delta) {
    tickMovement(delta);
}

void HotGhostMom::targetPlayerInRange() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i diff = position - playerPos;

    float distance = sqrt(pow(diff.x, 2) + pow(diff.y, 2));

    bool minRangeToPlayer = distance <= MIN_RANGE_TO_PLAYER;

    bool maxRangeToPlayer = distance >= MAX_RANGE_TO_PLAYER;

    if (!minRangeToPlayer && !maxRangeToPlayer) {
        moveTowardsPlayer();
    }
}

void HotGhostMom::moveTowardsPlayer() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    move(playerPos);
}