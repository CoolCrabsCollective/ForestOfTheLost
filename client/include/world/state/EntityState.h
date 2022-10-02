//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_STATE_H
#define LD51_CLIENT_STATE_H

#include "world/Entity.h"

class EntityState : public Tickable {
    Entity* entity;
    World* world;

public:
    EntityState(Entity* enemy);

    void tick(float delta) override;

    Entity* getEntity();

    World* getWorld();
};

#endif //LD51_CLIENT_STATE_H
