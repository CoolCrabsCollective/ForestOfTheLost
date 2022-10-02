//
// Created by william on 02/10/22.
//

#ifndef LD51_CLIENT_MONSTERCHARGESTATE_H
#define LD51_CLIENT_MONSTERCHARGESTATE_H

#include "EntityState.h"

class MonsterChargeState : public EntityState {
public:
    MonsterChargeState(Entity* monster);

    void tick(float delta) override;
};

#endif //LD51_CLIENT_MONSTERCHARGESTATE_H
