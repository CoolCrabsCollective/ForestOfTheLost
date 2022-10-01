//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_BUSH_H
#define LD51_CLIENT_BUSH_H


#include "HidingSpot.h"

class Bush : public HidingSpot {
public:
	Bush(World& world, const sf::Vector2i& position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD51_CLIENT_BUSH_H
