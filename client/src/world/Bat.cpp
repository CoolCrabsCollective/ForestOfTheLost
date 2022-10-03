//
// Created by cedric on 2022-10-02.
//

#include <GameAssets.h>
#include "world/Bat.h"

Bat::Bat(World &world, sf::Vector2i position) : Monster(world, position,
    world.getAssets().get(GameAssets::BAT),
    world.getAssets().get(GameAssets::SPOOKY_EYES)){
    attackMessage = {"A bat lands on your shoulder. It studies you with bright red eyes before bearing it's fangs.",
                     "You feel blood drizzling down your back before you pass out."};
}
