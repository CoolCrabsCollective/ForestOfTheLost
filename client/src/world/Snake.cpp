//
// Created by cedric on 2022-10-02.
//

#include "world/Snake.h"

#include <GameAssets.h>

Snake::Snake(World &world, sf::Vector2i position) : Monster(world, position,
                                                        world.getAssets().get(GameAssets::SNAKE),
                                                        world.getAssets().get(GameAssets::PACIFIC_EYES)){
    attackMessage = {"Hissssss! A slithering snake just bit you. Thankfully, it's not venomous!"};
}

void Snake::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {

    if(this->getRenderPosition().x < this->world.getPlayer().getRenderPosition().x)
    {
        daySprite.setScale(sf::Vector2f{1.0f, 1.0f});
    }
    else
    {
        daySprite.setScale(sf::Vector2f{-1.0f, 1.0f});
    }
    Monster::draw(target, states);
}

void Snake::drawDarkness(sf::RenderTarget &target) const {
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

