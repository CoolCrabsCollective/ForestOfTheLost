//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/Wraith.h"

Wraith::Wraith(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::INVISIBLE), world.getAssets().get(GameAssets::WRAITH)){
    attackMessage = "Cold. Why am I so cold? A piercing scream fills your ears. Your own.  A wraith has killed you.";
    scale = 3.0f;
}