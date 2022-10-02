//
// Created by cedric on 2022-10-01.
//

#ifndef LD51_CLIENT_TEDDYBEAR_H
#define LD51_CLIENT_TEDDYBEAR_H


#include "Item.h"

class TeddyBear : public Item {
public:
    explicit TeddyBear(World& world, sf::Vector2i position);

	bool activate() override;
};


#endif //LD51_CLIENT_TEDDYBEAR_H
