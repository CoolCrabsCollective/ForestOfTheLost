//
// Created by cedric on 2022-10-03.
//

#include <GameAssets.h>
#include "world/Beholder.h"

Beholder::Beholder(World &world, sf::Vector2i position) : Monster(world, position,
                                                            world.getAssets().get(GameAssets::BEHOLDER),
                                                            world.getAssets().get(GameAssets::BEHOLDER_EYES)){
    attackMessage = "Spindly fingers tear into your flesh. Empty eye sockets stare into your soul. You have been killed by a ghoul.";
    scale = 3;
    scaleDark = 3;
}
