//
// Created by william on 02/10/22.
//

#include "world/state/MonsterIdleState.h"
#include "world/state/MonsterAttackState.h"
#include "world/Monster.h"

MonsterIdleState::MonsterIdleState(Entity *monster) : EntityState(monster) {
}

void MonsterIdleState::tick(float delta) {

}