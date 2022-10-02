//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_MONSTERATTACKSTATE_H
#define LD51_CLIENT_MONSTERATTACKSTATE_H

#include "EntityState.h"

class MonsterAttackState : public EntityState {
public:
    MonsterAttackState(Entity* monster);

    void tick(float delta) override;
};

#endif //LD51_CLIENT_MONSTERATTACKSTATE_H
