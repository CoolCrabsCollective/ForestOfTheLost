//
// Created by Winter on 01/10/2022.
//

#include "world/Bush.h"
#include "SFML/Graphics/Texture.hpp"

Bush::Bush(World& world, const sf::Vector2i& position)
	: HidingSpot(world, position) {

}

void Bush::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({static_cast<float>(position.x - 0.125f), -static_cast<float>(position.y + 0.25f)});
	sprite.setScale({ 1.25f / sprite.getTexture()->getSize().x, 1.25f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}
