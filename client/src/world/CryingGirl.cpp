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
                                           "Lily: I lost my mother when I was young. I saw my mother's ghostly silhouette at the edge of this forest. I entered and then became lost. Can you help me find my mother and bring her back here?"}, [&](){

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