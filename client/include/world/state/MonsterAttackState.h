//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_MONSTERATTACKSTATE_H
#define LD51_CLIENT_MONSTERATTACKSTATE_H

#include "EntityState.h"

class MonsterAttackState : public EntityState {
    Entity* target;

    float attackInterval = 5000.0;

    float timeSinceLastAttack = 0.0;

public:
    MonsterAttackState(Entity* monster, Entity* target);

    void tick(float delta) override;
};

#endif //LD51_CLIENT_MONSTERATTACKSTATE_H
