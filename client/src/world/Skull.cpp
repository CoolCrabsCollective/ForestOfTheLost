//
// Created by cedric on 2022-10-03.
//

#include "world/Skull.h"
#include <GameAssets.h>

Skull::Skull(World &world, sf::Vector2i position) : Monster(world, position,
                                                                  world.getAssets().get(GameAssets::SKULL),
                                                                  world.getAssets().get(GameAssets::SKULL_EYES)){
    attackMessage = "A spooky scary skeleton sends shivers down your spine.... The shrieking skull shocks your soul and seals your doom tonight...";
    scale = 2;
    scaleDark = 2;
}
