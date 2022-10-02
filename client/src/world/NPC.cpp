//
// Created by Winter on 02/10/2022.
//

#include <utility>

#include "world/NPC.h"
#include "world/World.h"


NPC::NPC(World& world, sf::Vector2i position, std::map<Direction, sf::Texture*> textureMap)
	: Entity(world), textureMap(std::move(textureMap)) {
	this->position = position;
}

bool NPC::activate() {
	sf::Vector2i diff = getWorld().getPlayer().getPosition() - getPosition();

	for(Direction direction : { NORTH, EAST, WEST, SOUTH }) {
		if(directionToUnitVector(direction) == diff) {
			currentDir = direction;
			break;
		}
	}
	return true;
}

bool NPC::isBlocking(sf::Vector2i vec) {
	return vec == position;
}

void NPC::tick(float delta) {

}

void NPC::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	sprite.setTexture(*textureMap.at(currentDir), true);
	sprite.setPosition({position.x - 0.5f, -position.y - 1.0f});
	sprite.setScale({ 2.0f / sprite.getTexture()->getSize().x, 2.0f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}
