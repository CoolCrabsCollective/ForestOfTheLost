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

    targetPlayerInRange();
}

void HotGhostMom::targetPlayerInRange() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i diff = position - playerPos;

    float distance = sqrt(pow(diff.x, 2) + pow(diff.y, 2));

    bool maxRangeToPlayer = distance >= MAX_RANGE_TO_PLAYER;

    if (!maxRangeToPlayer) {
        moveTowardsPlayer();

        if (!removedOtherHotGhostMoms) {
            for (HotGhostMom* hotGhostMom : world.getHotGhostMoms()) {
                if (hotGhostMom != this) {
                    world.removeEntity(hotGhostMom);
                }
            }

            removedOtherHotGhostMoms = true;
        }
    }
}

void HotGhostMom::moveTowardsPlayer() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i moveTo = playerPos - MIN_RANGE_TO_PLAYER*vectorToUnitVector(playerPos);

    move(moveTo);
}

void HotGhostMom::findNewSpot() {

}

void HotGhostMom::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
}

void HotGhostMom::drawDarkness(sf::RenderTarget &target, sf::Shader* shader) const {
    daySprite.setPosition({renderPosition.x, -renderPosition.y});
    daySprite.setScale({ scale / daySprite.getTexture()->getSize().x, scale / daySprite.getTexture()->getSize().y });
    target.draw(daySprite, shader);
}