//
// Created by William on 01/10/2022.
//

#ifndef LD51_CLIENT_TREE_H
#define LD51_CLIENT_TREE_H


#include "HidingSpot.h"
#include "Solid.h"

class Tree : public HidingSpot, public Solid {
public:
    Tree(World& world, const sf::Vector2i& position);

    bool isBlocking(sf::Vector2i vec);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD51_CLIENT_TREE_H
