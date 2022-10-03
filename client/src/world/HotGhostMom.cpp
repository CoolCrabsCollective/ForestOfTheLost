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

    if (!cryingGirl) {
        targetPlayerInRange();
        checkForCryingGirl();
    } else if (position == destination && !ghostMomReachCryingGirl && playerTargeted) {
        // reached crying girl, start cutscene

        world.getDialogBox().startDialog({"Ghost Mom: Lily... I'm so happy to see you!", "Ghost Mom: Sir, thank you so much for bringing me back to Lily! This place is dangerous, be careful. There are many lost children in this forest. Some have been transformed into evil beings but they are simply children. Perhaps, bringing them toys could heal them."}, [&](){
            world.hotGhostMomInteraction(cryingGirl, this);
        });

        ghostMomReachCryingGirl = true;
    }
}

void HotGhostMom::targetPlayerInRange() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i diff = position - playerPos;

    float distance = sqrt(pow(diff.x, 2) + pow(diff.y, 2));

    bool maxRangeToPlayer = distance >= MAX_RANGE_TO_PLAYER;

    if (!maxRangeToPlayer) {
        playerTargeted = true;
        moveTowardsPlayer();
    } else {
        playerTargeted = false;
    }
}

void HotGhostMom::moveTowardsPlayer() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i moveTo = playerPos + MIN_RANGE_TO_PLAYER*vectorToUnitVector(playerPos);

    sf::Vector2i oldPos = position;

    move(moveTo);

    world.moveEntity(oldPos, this);
}

void HotGhostMom::findNewSpot() {

}

void HotGhostMom::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (cryingGirl && position == destination) {
        drawDarkness(target);
    }
}

void HotGhostMom::drawDarkness(sf::RenderTarget &target) const {
    daySprite.setPosition({renderPosition.x, -renderPosition.y});
    daySprite.setScale({ scale / daySprite.getTexture()->getSize().x, scale / daySprite.getTexture()->getSize().y });
    target.draw(daySprite);
}

void HotGhostMom::checkForCryingGirl() {
    for (int searchX = position.x  - searchGirlRadius ; searchX <= position.x + searchGirlRadius ; searchX++) {
        for (int searchY = position.y - searchGirlRadius; searchY <= position.y + searchGirlRadius; searchY++) {
            if (searchX == position.x && searchY == position.y)
                continue;

            auto entitiesAt = world.getEntitiesAt({searchX, searchY});

            for (Entity *entity: entitiesAt) {
                cryingGirl = dynamic_cast<CryingGirl *>(entity);

                if (cryingGirl) {
                    sf::Vector2i oldPos = position;
                    move(cryingGirl->getPosition() - vectorToUnitVector(cryingGirl->getPosition()));
                    world.moveEntity(oldPos, this);
                    return;
                }
            }
        }
    }
}
