//
// Created by william on 02/10/22.
//

#include "world/state/EntityState.h"

EntityState::EntityState(Entity *entity)  : entity(entity) {

}

void EntityState::tick(float delta) {
}

Entity* EntityState::getEntity() {
    return entity;
}

World* EntityState::getWorld() {
    return world;
}