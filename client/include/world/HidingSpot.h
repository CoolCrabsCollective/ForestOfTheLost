//
// Created by adrien on 01/10/22.
//

#ifndef LD51_CLIENT_HIDINGSPOT_H
#define LD51_CLIENT_HIDINGSPOT_H


#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"

class HidingSpot : public Entity {
    sf::Vector2i position;
    sf::Sprite sprite;
public:
    sf::Vector2i getPosition() const override;
    sf::Sprite getSprite() const;
    HidingSpot(sf::Vector2i position, sf::Sprite sprite);
};

#endif //LD51_CLIENT_HIDINGSPOT_H
