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
    float movingSpeed = 2;
    float rotationSpeed = 5;
    float scale = 1;
    float scaleDark = 1;

    sf::Vector2i partDestination = {};

    float searchRadius = 4;

    std::shared_ptr<EntityState> state;
    bool hasLookedForSpot = false;

    std::string attackMessage;

    float nextAttackCountdown = 0;
public:
    Monster(World &world, sf::Vector2i position, sf::Texture* dayTexture, sf::Texture* nightTexture);
    void tick(float delta) override;
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
    virtual void drawDarkness(sf::RenderTarget& target, sf::Shader* shader) const;
    sf::Vector2f getRenderPosition() const override;
    void findNewSpot();
    void moveTowardsPlayer();
    void move(sf::Vector2i des);

    void targetPlayerInRange();

    const std::shared_ptr<EntityState> &getState() const;

    void setState(const std::shared_ptr<EntityState> &state);

    std::string getAttackMessage();
};


#endif //LD51_CLIENT_MONSTER_H
