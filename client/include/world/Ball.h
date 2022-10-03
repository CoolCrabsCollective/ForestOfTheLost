//
// Created by Winter on 03/10/2022.
//

#ifndef LD51_CLIENT_BALL_H
#define LD51_CLIENT_BALL_H


#include "Item.h"

class Ball : public Item {
public:
	explicit Ball(World& world, sf::Vector2i position);

	bool activate() override;

	void draw(sf::RenderTarget &target, const sf::RenderStates &states) const;
};


#endif //LD51_CLIENT_BALL_H
