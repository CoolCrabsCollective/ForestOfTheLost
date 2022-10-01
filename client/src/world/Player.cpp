//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"
#include <optional>

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

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += delta*movingSpeed;

        if (actionProgress > 1) {
            position = destination;
            actionProgress = 0;
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(destination - position) * actionProgress;
        }
    } else if (rotating) {

    } else {

    }
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setTexture(*textureMap.at(currentDir));
	sprite.setPosition(renderPosition);
	//sprite.setScale(1.0f / sprite.getTexture())
}


