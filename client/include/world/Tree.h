//
// Created by William on 01/10/2022.
//

#ifndef LD51_CLIENT_TREE_H
#define LD51_CLIENT_TREE_H


#include "HidingSpot.h"
#include "Solid.h"
#include "Interactable.h"

enum TreeType {
	ALIVE,
	DEAD,
	THICK_DEAD
};

class Tree : public HidingSpot, public Solid, public Interactable {
	TreeType tree_type;
public:
    Tree(World& world, const sf::Vector2i& position, TreeType tree_type);

    bool isBlocking(sf::Vector2i vec);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	bool activate() override;
};


#endif //LD51_CLIENT_TREE_H
