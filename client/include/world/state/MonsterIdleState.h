//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_MONSTERIDLESTATE_H
#define LD51_CLIENT_MONSTERIDLESTATE_H

#include "EntityState.h"
#include "MonsterAttackState.h"

class MonsterIdleState : public EntityState {
public:
    MonsterIdleState(Entity *monster);

    void tick(float delta) override;
};

#endif //LD51_CLIENT_MONSTERIDLESTATE_H
