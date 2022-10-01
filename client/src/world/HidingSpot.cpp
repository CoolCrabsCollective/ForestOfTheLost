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

HidingSpot::HidingSpot(World &world, sf::Vector2i position, sf::Sprite sprite) : Entity(world) {
    this->position = position;
    this->sprite = sprite;
}

void HidingSpot::tick(float delta) {
}

void HidingSpot::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    /*
    sprite.setTexture(*textureMap.at(currentDir));
    sprite.setPosition(renderPosition);
    //sprite.setScale(1.0f / sprite.getTexture())
     */
}

