//
// Created by adrien on 01/10/22.
//

#ifndef LD51_CLIENT_HIDINGSPOT_H
#define LD51_CLIENT_HIDINGSPOT_H


#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "world/World.h"
#include "Direction.h"

class HidingSpot : public Entity {
protected:
    mutable sf::Sprite sprite;
public:
    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    virtual void shake() = 0;
    HidingSpot(World &world, sf::Vector2i position);
};

#endif //LD51_CLIENT_HIDINGSPOT_H
