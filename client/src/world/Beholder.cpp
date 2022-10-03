//
// Created by cedric on 2022-10-03.
//

#include <GameAssets.h>
#include "world/Beholder.h"

Beholder::Beholder(World &world, sf::Vector2i position) : Monster(world, position,
                                                            world.getAssets().get(GameAssets::BEHOLDER),
                                                            world.getAssets().get(GameAssets::BEHOLDER_EYES)){
    attackMessage = {"A foul creature from another plane appears before you. Teeth from the beholder's jaw tear your flesh, shredding your skin while looking at you with that giant eyeball."};
    scale = 3;
    scaleDark = 3;
}
