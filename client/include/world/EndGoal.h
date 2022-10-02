//
// Created by william on 01/10/22.
//

#ifndef LD51_CLIENT_ENDGOAL_H
#define LD51_CLIENT_ENDGOAL_H

#include "Entity.h"
#include "SFML/Graphics/Sprite.hpp"
#include "Solid.h"

class EndGoal : public Entity, public Solid {
protected:
    mutable sf::Sprite sprite;
public:
    EndGoal(World& world, const sf::Vector2i& position);

    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    bool isBlocking(sf::Vector2i vec);


};

#endif //LD51_CLIENT_ENDGOAL_H
