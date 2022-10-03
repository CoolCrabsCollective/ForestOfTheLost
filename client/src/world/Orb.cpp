//
// Created by william on 03/10/22.
//

#include "world/Orb.h"
#include <GameAssets.h>

Orb::Orb(World &world, sf::Vector2i position) : Monster(world, position,
                                                                        world.getAssets().get(GameAssets::ORB),
                                                                        world.getAssets().get(GameAssets::ORB)){
    attackMessage = "Bruh, these orbs aren't supposed to kill you. Lmao";
    scale = 2;
}

void Orb::tick(float delta) {
    if(!hasLookedForSpot) {
        findNewSpot();
        hasLookedForSpot = true;
    }

    tickMovement(delta);
}

void Orb::targetPlayerInRange() {
}

void Orb::moveTowardsPlayer() {
}

void Orb::findNewSpot() {

}