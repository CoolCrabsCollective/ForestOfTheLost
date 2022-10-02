//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/GroundHog.h"

GroundHog::GroundHog(World &world, sf::Vector2i position) : Monster(world, position, world.getAssets().get(GameAssets::GROUND_HOG), world.getAssets().get(GameAssets::PACIFIC_EYES)){

}
