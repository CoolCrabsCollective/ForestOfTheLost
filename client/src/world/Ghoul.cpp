//
// Created by cedric on 2022-10-02.
//

#include "world/Ghoul.h"
#include <GameAssets.h>

Ghoul::Ghoul(World &world, sf::Vector2i position) : Monster(world, position,
                                                        world.getAssets().get(GameAssets::GHOUL),
                                                        world.getAssets().get(GameAssets::SPOOKY_EYES)){
    attackMessage = "Thin spindly figures tear into your flesh. You stare into the empty eye sockets of your killed. You have been killed by a ghoul.";
    scale = 2;
}
