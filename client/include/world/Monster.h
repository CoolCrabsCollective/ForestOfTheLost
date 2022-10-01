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
    sf::Vector2f renderPosition = {};
    Direction currentDir = NORTH;
    Direction destinationDir = NORTH;
    float actionProgress = 0;
    float movingSpeed = 0.5;
    float rotationSpeed = 5;
public:
    Monster(World &world, sf::Vector2i position);
    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    void findNewSpot();
};


#endif //LD51_CLIENT_MONSTER_H
