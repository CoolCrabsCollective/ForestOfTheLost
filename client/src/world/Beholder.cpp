//
// Created by cedric on 2022-10-03.
//

#include <GameAssets.h>
#include "world/Beholder.h"

Beholder::Beholder(World &world, sf::Vector2i position) : Monster(world, position,
                                                            world.getAssets().get(GameAssets::BEHOLDER),
                                                            world.getAssets().get(GameAssets::BEHOLDER_EYES)){
    attackMessage = {"A foul creature from another plane appears before you...",
                     "It rips off your arm with it's powerful jaw...",
                     "It watches you die with it's unique giant eyeball."};
    scale = 3;
    scaleDark = 3;
}
