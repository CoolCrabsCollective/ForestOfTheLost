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
    getWorld().getDialogBox().startDialog({"Lily: *crying*",
                                           "You: What's wrong?",
                                           "Lily: My mother passed away when I was a baby. I thought I saw her at the edge of this forest...",
                                           "Lily: Now I'm lost. Bring her back to me please mister?"}, [&](){

        if (!removedOtherGirls) {
            for (CryingGirl* cryingGirl : world.getCryingGirls()) {
                if (cryingGirl != this) {
                    world.removeEntity(cryingGirl);
                }
            }

			world.setHotGhostMomsCanSpawn();
            world.setSetCheckPoint(true);

            removedOtherGirls = true;
        }
    });
    return NPC::activate();
}