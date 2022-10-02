//
// Created by William on 01/10/2022.
//

#include "world/Tree.h"
#include "SFML/Graphics/Texture.hpp"
#include "GameAssets.h"

Tree::Tree(World& world, const sf::Vector2i& position, TreeType tree_type)
	: HidingSpot(world, position), Solid() {
	sf::Texture* tex;
	switch(tree_type) {
		case ALIVE:
			tex = world.getAssets().get(GameAssets::ALIVE_TREE);
			break;

		case DEAD:
			tex = world.getAssets().get(GameAssets::DEAD_TREE);
			break;

		case THICK_DEAD:
			tex = world.getAssets().get(GameAssets::THICK_DEAD_TREE);
			break;
	}
	this->sprite.setTexture(*tex, true);
}

bool Tree::isBlocking(sf::Vector2i vec) {
    return vec == position;
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({static_cast<float>(position.x - 1.5f), -static_cast<float>(position.y + 2.5f)});
	sprite.setScale({ 3.5f / sprite.getTexture()->getSize().x, 3.5f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}
