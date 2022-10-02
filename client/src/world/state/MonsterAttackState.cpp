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
    Monster* monster = dynamic_cast<Monster*>(getEntity());

    Player* player = dynamic_cast<Player*>(target);

    sf::Vector2i targetPos = player->getPosition();

    sf::Vector2i posDiff = targetPos - monster->getPosition();

    sf::Vector2i unitVec = vectorToUnitVector(posDiff);

    if (posDiff != unitVec) {
        monster->setState(std::make_shared<MonsterIdleState>(monster));
        return;
    }

    timeSinceLastAttack += delta;
    if (timeSinceLastAttack >= attackInterval) {
        player->damage(1);
        timeSinceLastAttack = 0;
    }
}