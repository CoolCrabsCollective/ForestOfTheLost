//
// Created by adrien on 01/10/22.
//

#include "world/Monster.h"
#include "GameAssets.h"
#include "world/state/MonsterChargeState.h"
#include "world/state/MonsterAttackState.h"
#include <SFML/Graphics/RenderTarget.hpp>

Monster::Monster(World &world, sf::Vector2i position, sf::Texture* dayTexture, sf::Texture* nightTexture) : Entity(world),
    daySprite(*dayTexture),
    nightSprite(*nightTexture)
{
    this->position = position;
    this->movingStartPos = position;
    this->sprite = sf::Sprite(*world.getAssets().get(GameAssets::BAT));
    renderPosition = {static_cast<float>(position.x), static_cast<float>(-position.y)};

    state = std::make_shared<MonsterIdleState>(this);
    findNewSpot(); // make sure to spawn the monsters after the hiding spots exist in the world!
}

void Monster::tick(float delta) {
    bool moving = movingStartPos != destination;
    bool rotating = currentDir != destinationDir;

    renderPosition = (sf::Vector2f) movingStartPos;
    if (moving) {
        actionProgress += (delta / 1000) * movingSpeed;

        if (actionProgress > 1) {
            sf::Vector2i oldPos = movingStartPos;
            movingStartPos = destination;
            position = destination;
            world.moveEntity(oldPos, this);
            actionProgress = 0;

            state = std::make_shared<MonsterIdleState>(this);
        } else {
            renderPosition = (sf::Vector2f) movingStartPos + sf::Vector2f(destination - movingStartPos) * actionProgress;
            position = (sf::Vector2i) renderPosition;
        }
    } else if (rotating) {
        actionProgress += (delta / 1000) * rotationSpeed;

        if (actionProgress > 1) {
            currentDir = destinationDir;
            actionProgress = 0;
        }
    }

    state->tick(delta);
}

void Monster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (position == destination)
        return;

    daySprite.setPosition({renderPosition.x, -renderPosition.y});
    daySprite.setScale({ 1.0f / daySprite.getTexture()->getSize().x, 1.0f / daySprite.getTexture()->getSize().y });
    target.draw(daySprite);
}


void Monster::drawDarkness(sf::RenderTarget &target, sf::Shader* shader) const {
    nightSprite.setPosition({renderPosition.x, -renderPosition.y});
    nightSprite.setScale({ 1.0f / nightSprite.getTexture()->getSize().x, 1.0f / nightSprite.getTexture()->getSize().y });
    target.draw(nightSprite, shader);
}

void Monster::findNewSpot() {
    if (!dynamic_pointer_cast<MonsterIdleState>(state).get())
        return;

    // Find the closest hiding spot
    for (int searchX = position.x  - searchRadius ; searchX <= position.x + searchRadius ; searchX++) {
        for (int searchY = position.y  - searchRadius ; searchY <= position.y + searchRadius ; searchY++) {
            if (searchX == position.x && searchY == position.y)
                continue;

            // TODO: check no one else is going there

            auto entitiesAt = world.getEntitiesAt({searchX, searchY});

            for (int k = 0 ; k < entitiesAt.size() ; k++) {
                if(HidingSpot* spot = dynamic_cast<HidingSpot*>(entitiesAt.at(k))) {
                    destination = spot->getPosition();
                    return;
                }
            }
        }
    }
}

void Monster::moveTowardsPlayer() {
    if (dynamic_pointer_cast<MonsterChargeState>(state).get()) {
        sf::Vector2i playerPos = world.getPlayer().getPosition();

        sf::Vector2i posDiff = playerPos - position;

        sf::Vector2i unitVec = vectorToUnitVector(posDiff);

        if (posDiff == unitVec) {
            state = std::make_shared<MonsterAttackState>(this, &world.getPlayer());
        }

        destination = position + unitVec;
    }
}

sf::Vector2f Monster::getRenderPosition() const {
    return renderPosition;
}

const std::shared_ptr<EntityState> &Monster::getState() const {
    return state;
}

void Monster::setState(const std::shared_ptr<EntityState> &state) {
    Monster::state = state;
}

