//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/GroundHog.h"

GroundHog::GroundHog(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::GROUND_HOG), world.getAssets().get(GameAssets::PACIFIC_EYES)){
    attackMessage = {"A cute groundhog bumps into you. Watch out, next time it may be something a lot more dangerous!"};
}

void GroundHog::drawDarkness(sf::RenderTarget &target) const {

    if(this->getRenderPosition().x < this->world.getPlayer().getRenderPosition().x)
    {
        nightSprite.setScale(sf::Vector2f{1.0f, 1.0f});
    }
    else
    {
        nightSprite.setScale(sf::Vector2f{-1.0f, 1.0f});
    }

    Monster::drawDarkness(target);
}
