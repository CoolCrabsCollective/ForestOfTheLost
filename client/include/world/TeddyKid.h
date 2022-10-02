//
// Created by Winter on 02/10/2022.
//

#ifndef LD51_CLIENT_TEDDYKID_H
#define LD51_CLIENT_TEDDYKID_H


#include "NPC.h"

class TeddyKid : public NPC {
public:
	TeddyKid(World& world, const sf::Vector2i& position);

	bool activate() override;
};


#endif //LD51_CLIENT_TEDDYKID_H
