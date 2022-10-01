//
// Created by adrien on 01/10/22.
//

#include "world/HidingSpot.h"
#include "GameAssets.h"
#include <SFML/Graphics/RenderTarget.hpp>

HidingSpot::HidingSpot(World &world, sf::Vector2i position) : Entity(world) {
    this->position = position;
    this->sprite = sf::Sprite(*world.getAssets().get(GameAssets::HIDING_SPOT));
}

void HidingSpot::tick(float delta) {
}

void HidingSpot::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
    sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
    target.draw(sprite);
}

