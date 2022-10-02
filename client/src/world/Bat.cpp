//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/Bat.h"

Bat::Bat(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::BAT)){

}
