//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"
#include <optional>
#include "world/World.h"
#include "GameAssets.h"
#include "world/Direction.h"
#include "world/Interactable.h"

Player::Player(World& world)
	: Entity(world),
	  Alive<int>(3),
	  textureMap(),
	  Solid(),
	  currentDir(NORTH),
	  destinationDir(NORTH),
	  interactSound(),
	  noInteractSound() {
	textureMap[Direction::NORTH] = world.getAssets().get(GameAssets::PLAYER_BACK);
	textureMap[Direction::SOUTH] = world.getAssets().get(GameAssets::PLAYER_FRONT);
	textureMap[Direction::EAST] = world.getAssets().get(GameAssets::PLAYER_RIGHT);
	textureMap[Direction::WEST] = world.getAssets().get(GameAssets::PLAYER_LEFT);

	interactSound.setBuffer(*world.getAssets().get(GameAssets::INTERACT));
	noInteractSound.setBuffer(*world.getAssets().get(GameAssets::NOINTERACT));
	collisionSound.setBuffer(*world.getAssets().get(GameAssets::COLLISION));
}

sf::Vector2f Player::getRenderPosition() const {
    return renderPosition;
}

void Player::move(std::optional<Direction> direction) {
    inputDir = direction;
}

void Player::tick(float delta) {

	if(lastCollision > std::chrono::system_clock::now() - std::chrono::milliseconds(500))
		return;

    bool moving = position != destination;
    bool rotating = currentDir != destinationDir;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += (delta / 1000) * movingSpeed;

        if (actionProgress > 1) {
            sf::Vector2i oldPos = position;
            position = destination;
			renderPosition = (sf::Vector2f) position;
            world.moveEntity(oldPos, this);
            actionProgress = 0;
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(destination - position) * actionProgress;
        }
    } else if (rotating) {
		if(inputDir.has_value() && inputDir.value() != destinationDir) {
			currentDir = destinationDir;
			destinationDir = inputDir.value();
			actionProgress = 0;
		} else {
			actionProgress += (delta / 1000) * rotationSpeed;

			if (actionProgress > 1) {
				currentDir = destinationDir;
				actionProgress = 0;
			}
		}
    } else if (inputDir.has_value()) {
		if(inputDir.value() == currentDir) {
            destination = position + directionToUnitVector(inputDir.value());
            if (world.tileOccupied(destination, this) || lockMovement) {
                destination = position;
				if(!lockMovement) {
					collisionSound.play();
					lastCollision = std::chrono::system_clock::now();
				}
            }
        } else
			destinationDir = inputDir.value();
    }

    world.checkEntitesInRange(this, 1);
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setTexture(*textureMap.at(destinationDir), true);
	sprite.setPosition({renderPosition.x - 0.5f, -renderPosition.y - 1.0f});
	sprite.setScale({ 2.0f / sprite.getTexture()->getSize().x, 2.0f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}

void Player::setLockMovement(bool lockMovement) {
    Player::lockMovement = lockMovement;
}

bool Player::isBlocking(sf::Vector2i vec) {
    return vec == position || vec == destination;
}

int Player::getZOrder() const {
	return -1;
}

bool Player::isLockMovement() const {
    return lockMovement;
}

void Player::interact() {
	if(lastInteract > std::chrono::system_clock::now() - std::chrono::milliseconds(500))
		return;

	for(Entity* entity : world.getEntitiesAt(position + directionToUnitVector(currentDir)))
		if(Interactable* interactable = dynamic_cast<Interactable*>(entity))
		{
			if(!interactable->activate())
				continue;
			lastInteract = std::chrono::system_clock::now();
			interactSound.play();
			return;
		}


	lastInteract = std::chrono::system_clock::now();
	noInteractSound.play();
}


