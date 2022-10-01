//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"

sf::Vector2i Player::getPosition() const {
	return position;
}

/*
 * Rotate player in direction of movement
 * check collision
 * move player between grids
 */
void Player::move(sf::Vector2i direction) {
    if (heading != direction)
        rotateToHeading(direction);
}

void rotateToHeading(sf::Vector2i direction) {

}

bool Player::checkCollision() {
    return false;
}
