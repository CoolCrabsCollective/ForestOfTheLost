//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"
#include <optional>
#include "world/World.h"
#include "GameAssets.h"
#include "world/Direction.h"

Player::Player(World& world) : Entity(world), Alive<int>(3), textureMap(), Solid() {
	textureMap[Direction::NORTH] = world.getAssets().get(GameAssets::PLAYER_BACK);
	textureMap[Direction::SOUTH] = world.getAssets().get(GameAssets::PLAYER_FRONT);
	textureMap[Direction::EAST] = world.getAssets().get(GameAssets::PLAYER_RIGHT);
	textureMap[Direction::WEST] = world.getAssets().get(GameAssets::PLAYER_LEFT);
}

sf::Vector2f Player::getRenderPosition() const {
    return renderPosition;
}

void Player::move(std::optional<Direction> direction) {
    inputDir = direction;
}

void Player::tick(float delta) {
    bool moving = position != destination;
    bool rotating = currentDir != destinationDir;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += (delta / 1000) * movingSpeed;

        if (actionProgress > 1) {
            sf::Vector2i oldPos = position;
            position = destination;
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
            if (world.tileOccupied(destination, this)) {
                destination = position;
            }
        } else
			destinationDir = inputDir.value();
    }
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setTexture(*textureMap.at(destinationDir));
	sprite.setPosition({renderPosition.x, -renderPosition.y});
	sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}

bool Player::isBlocking(sf::Vector2i vec) {
    return vec == position || vec == destination;
}

int Player::getZOrder() const {
	return -1;
}


