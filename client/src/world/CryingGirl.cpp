//
// Created by william on 02/10/22.
//

#include "world/CryingGirl.h"
#include "world/World.h"
#include "GameAssets.h"

CryingGirl::CryingGirl(World& world, const sf::Vector2i& position)
        : NPC(world, position, {{NORTH, world.getAssets().get(GameAssets::CRYING_GIRL_BACK)},
                                {SOUTH, world.getAssets().get(GameAssets::CRYING_GIRL_FRONT)},
                                {EAST, world.getAssets().get(GameAssets::CRYING_GIRL_RIGHT)},
                                {WEST, world.getAssets().get(GameAssets::CRYING_GIRL_LEFT)}}) {}

bool CryingGirl::activate() {
    getWorld().getDialogBox().startDialog({"Crying girl: I'm vewy sad wah.",
                                           "You: What's wrong?",
                                           "Crying girl: My fwiend do be dead 0w0"}, [&](){

        if (!removedOtherGirls) {
            for (CryingGirl* cryingGirl : world.getCryingGirls()) {
                if (cryingGirl != this) {
                    world.removeEntity(cryingGirl);
                }
            }

            world.spawnHotGhostMoms(this);

            world.setSetCheckPoint(true);

            removedOtherGirls = true;
        }
    });
    return NPC::activate();
}