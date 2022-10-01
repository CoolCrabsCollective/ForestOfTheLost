//
// Created by adrien on 01/10/22.
//

#ifndef LD51_CLIENT_MONSTER_H
#define LD51_CLIENT_MONSTER_H


#include "World.h"
#include "HidingSpot.h"

class Monster : public Entity {
    mutable sf::Sprite sprite;
    bool findingNewSpot;
    HidingSpot* closestHidingSpot;
    sf::Vector2f renderPosition = {};
public:
    Monster(World &world, sf::Vector2i position);
    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    void findNewSpot();
};


#endif //LD51_CLIENT_MONSTER_H
