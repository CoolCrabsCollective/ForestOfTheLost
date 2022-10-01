//
// Created by adrien on 01/10/22.
//

#include "world/HidingSpot.h"

sf::Vector2i HidingSpot::getPosition() const {
    return position;
}
sf::Sprite HidingSpot::getSprite() const {
    return sprite;
}

HidingSpot::HidingSpot(sf::Vector2i position, sf::Sprite sprite) {
    this->position = position;
    this->sprite = sprite;
}
