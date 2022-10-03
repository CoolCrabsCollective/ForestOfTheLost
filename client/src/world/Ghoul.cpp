//
// Created by cedric on 2022-10-02.
//

#include "world/Ghoul.h"
#include <GameAssets.h>

Ghoul::Ghoul(World &world, sf::Vector2i position) : Monster(world, position,
                                                        world.getAssets().get(GameAssets::GHOUL),
                                                        world.getAssets().get(GameAssets::SPOOKY_EYES)){
    attackMessage = {"Spindly fingers tear into your flesh. Empty eye sockets stare into your soul...",
                    "You have been killed by a ghoul."};
    scale = 2;
}
