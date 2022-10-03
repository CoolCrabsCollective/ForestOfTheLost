//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_CRYINGGIRL_H
#define LD51_CLIENT_CRYINGGIRL_H

#include "NPC.h"

class CryingGirl : public NPC {
    bool removedOtherGirls = false;

public:
    CryingGirl(World& world, const sf::Vector2i& position);

    bool activate() override;
};

#endif //LD51_CLIENT_CRYINGGIRL_H
