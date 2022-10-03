//
// Created by William on 01/10/2022.
//

#include "world/Tree.h"
#include "SFML/Graphics/Texture.hpp"
#include "GameAssets.h"

Tree::Tree(World& world, const sf::Vector2i& position, TreeType tree_type)
	: HidingSpot(world, position), Solid(), tree_type(tree_type) {
	sf::Texture* tex;
	switch(tree_type) {
		case ALIVE:
			tex = world.getAssets().get(GameAssets::ALIVE_TREE);
			break;

		case SQUIRREL:
			tex = world.getAssets().get(GameAssets::SQUIRREL_TREE);
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

bool Tree::activate() {
	if(tree_type == ALIVE)
		world.getDialogBox().startDialog({ "This tree looks normal." });
	else if(tree_type == SQUIRREL)
		world.getDialogBox().startDialog({ "This tree has a squirrel family living in it!" });
	else if(tree_type == DEAD)
		world.getDialogBox().startDialog({ "This tree looks creepy." });
	else
		world.getDialogBox().startDialog({ "Rats and spiders escape from this large dead tree." });
	return true;
}

void Tree::shake() {

}
