//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"
#include <optional>

sf::Vector2i Player::getPosition() const {
	return position;
}

sf::Vector2f Player::getRenderPosition() const {
    return renderPosition;
}

void Player::move(std::optional<Direction> direction) {
    inputDir = direction;
}

void Player::tick(float delta) {
    bool moving = position != destination;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += delta*movingSpeed;

        if (actionProgress > 1) {
            position = destination;
            actionProgress = 0;
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(destination - position)*actionProgress;
        }
    } else if (rotating) {

    } else {

    }
}


