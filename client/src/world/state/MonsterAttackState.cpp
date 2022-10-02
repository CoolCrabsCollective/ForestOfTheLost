//
// Created by william on 02/10/22.
//

#include "world/state/MonsterAttackState.h"
#include "world/state/MonsterIdleState.h"
#include "world/World.h"
#include "world/Monster.h"

MonsterAttackState::MonsterAttackState(Entity *monster, Entity* target) : EntityState(monster), target(target) {
}

void MonsterAttackState::tick(float delta) {
}