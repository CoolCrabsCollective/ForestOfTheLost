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
    closestHidingSpot = nullptr;
    findNewSpot(); // not good! What if the entities aren't added yet
}

void Monster::tick(float delta) {
   if (!findingNewSpot || closestHidingSpot == nullptr)
       return;

   float speed = 0.001f;
   if (closestHidingSpot->getPosition().x > renderPosition.x)
       renderPosition.x += speed;
   else
       renderPosition.x -= speed;

    if (closestHidingSpot->getPosition().y > renderPosition.y)
        renderPosition.y += speed;
    else
        renderPosition.y -= speed;
}

void Monster::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (!findingNewSpot)
        return;

    sprite.setPosition(renderPosition);
    sprite.setScale({ 1.0f / sprite.getTexture()->getSize().x, 1.0f / sprite.getTexture()->getSize().y });
    target.draw(sprite);
}

void Monster::findNewSpot() {
    findingNewSpot = true;
    // Find the closest hiding spot
    for (int i = 0 ; i < world.getEntities().size() ; i++) {
        if(HidingSpot* spot = dynamic_cast<HidingSpot*>(world.getEntities().at(i))) {
            if (closestHidingSpot == nullptr || ((abs(position.x - spot->getPosition().x) + (position.y - spot->getPosition().y) < (abs(position.x - closestHidingSpot->getPosition().x) + (position.y - closestHidingSpot->getPosition().y))))) {
                closestHidingSpot = spot;
            }
        }
    }
}
