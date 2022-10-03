//
// Created by Winter on 01/10/2022.
//

#ifndef LD51_CLIENT_BUSH_H
#define LD51_CLIENT_BUSH_H


#include "HidingSpot.h"

enum BushType {
    BUSH,
    BUSH2,
    WITHERED_BUSH,
    WITHERED_BUSH2
};

class Bush : public HidingSpot {
public:
	Bush(World& world, const sf::Vector2i& position, BushType bushType);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

protected:
    BushType bush_type;
};


#endif //LD51_CLIENT_BUSH_H
