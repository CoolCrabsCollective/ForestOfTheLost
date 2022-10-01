//
// Created by William on 01/10/2022.
//

#include "world/Tree.h"
#include "SFML/Graphics/Texture.hpp"
#include "GameAssets.h"

Tree::Tree(World& world, const sf::Vector2i& position)
	: HidingSpot(world, position), Solid() {
    this->sprite = sf::Sprite(*world.getAssets().get(GameAssets::TREE));
}

bool Tree::isBlocking(sf::Vector2i vec) {
    return vec == position;
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({static_cast<float>(position.x - 1.5f), -static_cast<float>(position.y + 2.5f)});
	sprite.setScale({ 3.5f / sprite.getTexture()->getSize().x, 3.5f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}
