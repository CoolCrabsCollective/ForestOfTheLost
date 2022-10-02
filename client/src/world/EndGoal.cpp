//
// Created by william on 01/10/22.
//

#include "world/EndGoal.h"
#include "GameAssets.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "world/World.h"

EndGoal::EndGoal(World &world, const sf::Vector2i &position) : Entity(world), Solid() {
    this->position = position;
    this->sprite = sf::Sprite(*world.getAssets().get(GameAssets::END_GOAL));
}

void EndGoal::tick(float delta) {
}

void EndGoal::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setPosition({static_cast<float>(position.x), -static_cast<float>(position.y)});
    sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
    target.draw(sprite);
}

bool EndGoal::isBlocking(sf::Vector2i vec) {
    return vec == position;
}

