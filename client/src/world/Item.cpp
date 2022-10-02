//
// Created by cedric on 2022-10-01.
//

#include "world/Item.h"

Item::Item(World& world, sf::Texture* texture, sf::Vector2i position): Entity(world), sprite(*texture){
    this->position = position;
}


void Item::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
	if(taken)
		return;

    sprite.setPosition({static_cast<float>(position.x), static_cast<float>(-position.y)});
    sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
    target.draw(sprite);
}

bool Item::isBlocking(sf::Vector2i vec) {
    return !taken && vec == this->position;
}

void Item::tick(float delta) {

}
