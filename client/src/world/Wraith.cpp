//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/Wraith.h"

Wraith::Wraith(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::INVISIBLE), world.getAssets().get(GameAssets::WRAITH)){
    attackMessage = "Cold. So cold. A piercing scream fills your ears. A wraith has killed you.";
    scale = 4.0f;
}