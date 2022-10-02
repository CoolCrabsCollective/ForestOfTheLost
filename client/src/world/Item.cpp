//
// Created by cedric on 2022-10-01.
//

#include "world/Item.h"

Item::Item(World &world, sf::Sprite sprite) : Entity(world), sprite(sprite){

}


void Item::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {

}

