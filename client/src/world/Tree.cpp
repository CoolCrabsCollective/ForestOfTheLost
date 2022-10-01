//
// Created by Winter on 01/10/2022.
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
