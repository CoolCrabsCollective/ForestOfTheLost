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

void Bush::shake() {
    bush_is_shaking = true;
    bush_delta = 0.0f;
}

void Bush::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sprite.setScale({ 1.25f / sprite.getTexture()->getSize().x, 1.25f / sprite.getTexture()->getSize().y });

    sprite.setOrigin({sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f});
	sprite.setPosition({static_cast<float>(position.x) - 0.125f + 1.25f/2.0f,
                     -static_cast<float>(position.y) - 0.25f + 1.25f/2.0f});

	if(bush_is_shaking)
	    sprite.setScale({sprite.getScale().x * bush_shake_scale.x, sprite.getScale().y * bush_shake_scale.y });
	target.draw(sprite);
}

void Bush::tick(float delta) {
    HidingSpot::tick(delta);
    if(bush_is_shaking)
    {
        bush_shake_scale = {
                1.0f + (std::cos(bush_shake_speed * bush_delta / 1000.f)) * bush_shake_intensity.x,
                1.0f + (std::cos(bush_shake_speed * bush_delta / 1000.f)) * bush_shake_intensity.y,
        };
        bush_delta += delta;
    }

    if(bush_delta >= bush_shake_time)
    {
        bush_is_shaking = false;
    }
}
