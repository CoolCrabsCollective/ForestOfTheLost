//
// Created by Winter on 01/10/2022.
//

#include <GameAssets.h>
#include "world/Bush.h"
#include "SFML/Graphics/Texture.hpp"

Bush::Bush(World& world, const sf::Vector2i& position, BushType bush)
	: HidingSpot(world, position), bush_type(bush) {
    sf::Texture* tex;
    switch(bush_type) {
        case BUSH:
            tex = world.getAssets().get(GameAssets::BUSH);
            break;

        case BUSH2:
            tex = world.getAssets().get(GameAssets::BUSH2);
            break;

        case WITHERED_BUSH:
            tex = world.getAssets().get(GameAssets::WITHERED_BUSH);
            break;

        case WITHERED_BUSH2:
            tex = world.getAssets().get(GameAssets::WITHERED_BUSH2);
            break;
        default:
            throw std::runtime_error("You're dumb");
    }
    this->sprite.setTexture(*tex, true);
}

void Bush::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({static_cast<float>(position.x - 0.125f), -static_cast<float>(position.y + 0.25f)});
	sprite.setScale({ 1.25f / sprite.getTexture()->getSize().x, 1.25f / sprite.getTexture()->getSize().y });
	target.draw(sprite);
}
