//
// Created by adrien on 01/10/22.
//

#include "world/Monster.h"
#include "GameAssets.h"
#include "world/World.h"
#include <SFML/Graphics/RenderTarget.hpp>

Monster::Monster(World &world, sf::Vector2i position, sf::Texture* dayTexture, sf::Texture* nightTexture) : Entity(world),
    daySprite(*dayTexture),
    nightSprite(*nightTexture)
{
    this->position = position;
    this->destination = position;
    this->partDestination = position;

    renderPosition = {static_cast<float>(position.x), static_cast<float>(-position.y)};

    attackMessage = "A monster attacked you!"; // shitty default attack message
}

void Monster::tick(float delta) {
    if (nextAttackCountdown > 0)
        nextAttackCountdown -= delta;

    if(!hasLookedForSpot) {
        findNewSpot();
        hasLookedForSpot = true;
    }

    tickMovement(delta);

    if (world.getPhase() == INITIAL && attacking && nextAttackCountdown < 1250) {
        world.setTimePaused(false);
        attacking = false;
    }

    if (nextAttackCountdown <= 0 && !world.isTimePaused()) {
        targetPlayerInRange();
        attacking = false;
    }

    if (position == world.getPlayer().getPosition() && nextAttackCountdown <= 0) {
        world.handleMonsterAttack(*this);
        nextAttackCountdown = 2000; // 2 seconds
        findNewSpot();

        attacking = true;
    }
}

void Monster::tickMovement(float delta) {
    bool moving = position != partDestination;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += (delta / 1000) / 0.25;

        if (actionProgress > 1) {
            sf::Vector2i oldPos = position;
            position = partDestination;
            renderPosition = (sf::Vector2f) position;
            world.moveEntity(oldPos, this);
            actionProgress = 0;

            if (partDestination != destination) {
                partDestination = position + vectorToUnitVector(destination - position);
            }

            world.shake(position);

            // Commented out: the bush sound is annoying AF
//            bushSound.play();
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(partDestination - position) * actionProgress;
        }
    }
}

void Monster::targetPlayerInRange() {
    sf::Vector2i playerPos = world.getPlayer().getPosition();

    sf::Vector2i diff = position - playerPos;

    bool nextToPlayer = diff.lengthSq() < 1.1;

    if (nextToPlayer) {
		world.gameOverSound.play();
		world.setTimePaused(true);
        moveTowardsPlayer();
    }
}

void Monster::move(sf::Vector2i des) {
    destination = des;
    partDestination = position + vectorToUnitVector(destination - position);
    world.shake(position);
}

void Monster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (position == destination)
        return;

    daySprite.setPosition({renderPosition.x - scale / 4.0f, -renderPosition.y - scale / 4.0f});
    daySprite.setScale({ scale / daySprite.getTexture()->getSize().x, scale / daySprite.getTexture()->getSize().y });
    target.draw(daySprite);
}

void Monster::drawDarkness(sf::RenderTarget &target) const {
    if(this->getWorld().getPhase() > GamePhase::INITIAL)
    {
        nightSprite.setPosition({renderPosition.x - scaleDark / 4.0f, -renderPosition.y - scaleDark / 4.0f});
        nightSprite.setScale({ scaleDark / nightSprite.getTexture()->getSize().x, scaleDark / nightSprite.getTexture()->getSize().y });
        target.draw(nightSprite);
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

			sf::Vector2i dest = {searchX, searchY};

			for(Monster* monster : world.get_monsters())
				if(monster->getDestination() == dest)
					continue;

            auto entitiesAt = world.getEntitiesAt(dest);

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

}

sf::Vector2f Monster::getRenderPosition() const {
    return renderPosition;
}

std::string Monster::getAttackMessage() {
    return attackMessage;
}

