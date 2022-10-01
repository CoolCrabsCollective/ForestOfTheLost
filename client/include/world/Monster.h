//
// Created by adrien on 01/10/22.
//

#ifndef LD51_CLIENT_MONSTER_H
#define LD51_CLIENT_MONSTER_H


#include "World.h"

class Monster : public Entity {
    mutable sf::Sprite sprite;
public:
    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    Monster(World &world, sf::Vector2i position);
};


#endif //LD51_CLIENT_MONSTER_H
