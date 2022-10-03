//
// Created by william on 03/10/22.
//

#include "world/Orb.h"
#include <GameAssets.h>

Orb::Orb(World &world, sf::Vector2i position) : Monster(world, position,
                                                                        world.getAssets().get(GameAssets::ORB),
                                                                        world.getAssets().get(GameAssets::ORB)){
    attackMessage = "Bruh, these orbs aren't supposed to kill you. Lmao";
    scale = 1;
    hasLookedForSpot = false;
}

void Orb::tick(float delta) {
    if(!hasLookedForSpot) {
        findNewSpot();
        hasLookedForSpot = true;
    }

    timeSinceLastMovement += delta;

    if (timeSinceLastMovement > movementInterval) {
        tickMovement(delta);
        timeSinceLastMovement = 0;
    }

    if (position == destination) {
        hasLookedForSpot = false;
    }
}

void Orb::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    daySprite.setPosition({renderPosition.x - scale / 4.0f, -renderPosition.y - scale / 4.0f});
    daySprite.setScale({ scale / daySprite.getTexture()->getSize().x, scale / daySprite.getTexture()->getSize().y });
    target.draw(daySprite);
}

void Orb::drawDarkness(sf::RenderTarget &target) const {
}

void Orb::targetPlayerInRange() {
}

void Orb::moveTowardsPlayer() {
}

void Orb::findNewSpot() {
    int randRadius = rand() % (int) searchRadius + 1;
    int randDir = rand() % 360 + 1;

    move(position + sf::Vector2i{static_cast<int>(cos(randDir) * randRadius), static_cast<int>(sin(randDir) * randRadius)});
}
