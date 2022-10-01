//
// Created by adrien on 01/10/22.
//

#include "world/Monster.h"
#include "GameAssets.h"
#include <SFML/Graphics/RenderTarget.hpp>

Monster::Monster(World &world, sf::Vector2i position) : Entity(world) {
    this->position = position;
    this->sprite = sf::Sprite(*world.getAssets().get(GameAssets::BAT));
    renderPosition = {static_cast<float>(position.x), static_cast<float>(-position.y)};
    findNewSpot(); // make sure to spawn the monsters after the hiding spots exist in the world!
}

void Monster::tick(float delta) {
    bool moving = position != destination;
    bool rotating = currentDir != destinationDir;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        actionProgress += (delta / 1000) * movingSpeed;

        if (actionProgress > 1) {
            sf::Vector2i oldPos = position;
            position = destination;
            world.moveEntity(oldPos, this);
            actionProgress = 0;
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(destination - position) * actionProgress;
        }
    } else if (rotating) {
        actionProgress += (delta / 1000) * rotationSpeed;

        if (actionProgress > 1) {
            currentDir = destinationDir;
            actionProgress = 0;
        }
    }
}

void Monster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (position == destination)
        return;

    sprite.setPosition({renderPosition.x, -renderPosition.y});
    sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
    target.draw(sprite);
}

void Monster::findNewSpot() {
    // Find the closest hiding spot
    for (int i = 0 ; i < world.getEntities().size() ; i++) {
        if(HidingSpot* spot = dynamic_cast<HidingSpot*>(world.getEntities().at(i))) {
            // Don't want to go to the same bush
            if (spot->getPosition() == position)
                continue;

            // TERRIBLE algorithm
            if ((position - spot->getPosition()).lengthSq() > 3*3)
                continue;

            destination = spot->getPosition();
        }
    }
}
