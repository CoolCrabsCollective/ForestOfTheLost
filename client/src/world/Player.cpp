//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"

Player::Player(World& world) : Entity(world), textureMap() {

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
    } else {
        switch (inputDir.value()) {
            case EAST:
                destination = position + sf::Vector2i{1,0};
                break;
            case NORTH:
                destination = position + sf::Vector2i{0,-1};
                break;
            case WEST:
                destination = position + sf::Vector2i{-1,0};
                break;
            case SOUTH:
                destination = position + sf::Vector2i{0,1};
                break;
        }
    }
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setTexture(*textureMap.at(currentDir));
	sprite.setPosition(renderPosition);
	//sprite.setScale(1.0f / sprite.getTexture())
}


