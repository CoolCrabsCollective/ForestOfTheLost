//
// Created by adrien on 01/10/22.
//

#ifndef LD51_CLIENT_MONSTER_H
#define LD51_CLIENT_MONSTER_H


#include "World.h"
#include "HidingSpot.h"
#include "state/MonsterIdleState.h"

class Monster : public Entity {
protected:
    mutable sf::Sprite daySprite;
    mutable sf::Sprite nightSprite;
    sf::Vector2f renderPosition = {};
    Direction currentDir = NORTH;
    Direction destinationDir = NORTH;
    float actionProgress = 0;
    float movingSpeed = 0.5;
    float rotationSpeed = 5;

    sf::Vector2i partDirection = {};

    float searchRadius = 7;

    float attackCoolDown = 0.0;
    float timeSinceLastAttack = 0.0;

    std::shared_ptr<EntityState> state;
public:
    Monster(World &world, sf::Vector2i position, sf::Texture* dayTexture, sf::Texture* nightTexture);
    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    virtual void drawDarkness(sf::RenderTarget& target, sf::Shader* shader) const;
    sf::Vector2f getRenderPosition() const override;
    void findNewSpot();
    void moveTowardsPlayer();

    const std::shared_ptr<EntityState> &getState() const;

    void setState(const std::shared_ptr<EntityState> &state);

    float getAttackCoolDown() const;

    void setAttackCoolDown(float attackCoolDown);

    float getTimeSinceLastAttack() const;

    void setTimeSinceLastAttack(float timeSinceLastAttack);
};


#endif //LD51_CLIENT_MONSTER_H
