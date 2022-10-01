//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"
#include <optional>
#include "world/World.h"
#include "GameAssets.h"
#include "world/Direction.h"

Player::Player(World& world) : Entity(world), HealthComponent<int>(3), textureMap() {
	textureMap[Direction::NORTH] = world.getAssets().get(GameAssets::PLAYER_BACK);
	textureMap[Direction::SOUTH] = world.getAssets().get(GameAssets::PLAYER_FRONT);
	textureMap[Direction::EAST] = world.getAssets().get(GameAssets::PLAYER_LEFT);
	textureMap[Direction::WEST] = world.getAssets().get(GameAssets::PLAYER_RIGHT);
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
        actionProgress += (delta / 1000)*movingSpeed;

        if (actionProgress > 1) {
            position = destination;
            actionProgress = 0;
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(destination - position) * actionProgress;
        }
    } else if (rotating) {
        actionProgress += (delta / 1000)*rotationSpeed;

        if (actionProgress > 1) {
            currentDir = destinationDir;
            actionProgress = 0;
        }
    } else if (inputDir.has_value()) {
        destination = position + directionToUnitVector(inputDir.value());
    }
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setTexture(*textureMap.at(currentDir));
	sprite.setPosition({renderPosition.x, -renderPosition.y});
	sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}


