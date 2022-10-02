//
// Created by adrien on 01/10/22.
//

#include "world/Monster.h"
#include "GameAssets.h"
#include "world/state/MonsterChargeState.h"
#include <SFML/Graphics/RenderTarget.hpp>

Monster::Monster(World &world, sf::Vector2i position, sf::Texture* dayTexture, sf::Texture* nightTexture) : Entity(world),
    daySprite(*dayTexture),
    nightSprite(*nightTexture)
{
    this->position = position;
    renderPosition = {static_cast<float>(position.x), static_cast<float>(-position.y)};

    state = std::make_shared<MonsterIdleState>(this);
    attackMessage = "A monster attacked you!"; // shitty default attack message
}

void Monster::tick(float delta) {
    if(!hasLookedForSpot) {

        findNewSpot();
        hasLookedForSpot = true;
    }

    bool moving = position != partDestination;
    bool rotating = currentDir != destinationDir;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += (delta / 1000) * movingSpeed;

        if (actionProgress > 1) {
            sf::Vector2i oldPos = position;
            position = partDestination;
            renderPosition = (sf::Vector2f) position;
            world.moveEntity(oldPos, this);
            actionProgress = 0;

            if (partDestination != destination) {
                partDestination = position + vectorToUnitVector(destination - position);
            }
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(partDestination - position) * actionProgress;
        }
    } else if (rotating) {
        if (actionProgress > 1) {
            currentDir = destinationDir;
        }
    }

    targetPlayerInRange();

    if (position == world.getPlayer().getPosition()) {
        world.handleMonsterAttack(*this);
    }

    state->tick(delta);
}

void Monster::targetPlayerInRange() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i diff = position - playerPos;

    bool nextToPlayer = diff == vectorToUnitVector(diff);

    if (nextToPlayer) {
        moveTowardsPlayer();
    }
}

void Monster::move(sf::Vector2i des) {
    destination = des;
    partDestination = position + vectorToUnitVector(destination - position);
}

void Monster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (position == destination)
        return;

    daySprite.setPosition({renderPosition.x, -renderPosition.y});
    daySprite.setScale({ 1.0f / daySprite.getTexture()->getSize().x, 1.0f / daySprite.getTexture()->getSize().y });
    target.draw(daySprite);
}

void Monster::drawDarkness(sf::RenderTarget &target, sf::Shader* shader) const {
    if(this->getWorld().getPhase() > GamePhase::INITIAL)
    {
        nightSprite.setPosition({renderPosition.x, -renderPosition.y});
        nightSprite.setScale({ 1.0f / nightSprite.getTexture()->getSize().x, 1.0f / nightSprite.getTexture()->getSize().y });
        target.draw(nightSprite, shader);
    }
}

void Monster::findNewSpot() {
    std::vector<sf::Vector2i> potentialSpots;

    // Find the closest hiding spot
    for (int searchX = position.x  - searchRadius ; searchX <= position.x + searchRadius ; searchX++) {
        for (int searchY = position.y  - searchRadius ; searchY <= position.y + searchRadius ; searchY++) {
            if (searchX == position.x && searchY == position.y)
                continue;

            // TODO: check no one else is going there
            // Update: this is kind of impossible fuck it

            auto entitiesAt = world.getEntitiesAt({searchX, searchY});

            for (int k = 0 ; k < entitiesAt.size() ; k++) {
                if(HidingSpot* spot = dynamic_cast<HidingSpot*>(entitiesAt.at(k))) {
                    potentialSpots.push_back(spot->getPosition());
                }
            }
        }
    }

    if (potentialSpots.size() != 0)
        move(potentialSpots.at(std::rand() % (potentialSpots.size())));
}

void Monster::moveTowardsPlayer() {
        sf::Vector2i playerPos = world.getPlayer().getPosition();

        move(playerPos);

        world.setTimePaused(true);
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

std::string Monster::getAttackMessage() {
    return attackMessage;
}

