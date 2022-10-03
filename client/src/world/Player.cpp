//
// Created by Winter on 01/10/2022.
//

#include "world/Player.h"
#include <optional>
#include <iostream>
#include "world/World.h"
#include "GameAssets.h"
#include "world/Direction.h"
#include "world/Interactable.h"

Player::Player(World& world)
	: Entity(world),
	  Alive<int>(3),
	  textureMap(),
	  Solid(),
	  currentDir(NORTH),
	  destinationDir(NORTH),
	  interactSound(),
	  noInteractSound(){
	textureMap[Direction::NORTH] = world.getAssets().get(GameAssets::PLAYER_BACK);
	textureMap[Direction::SOUTH] = world.getAssets().get(GameAssets::PLAYER_FRONT);
	textureMap[Direction::EAST] = world.getAssets().get(GameAssets::PLAYER_RIGHT);
	textureMap[Direction::WEST] = world.getAssets().get(GameAssets::PLAYER_LEFT);

	interactSound.setBuffer(*world.getAssets().get(GameAssets::INTERACT));
	noInteractSound.setBuffer(*world.getAssets().get(GameAssets::NOINTERACT));
	collisionSound.setBuffer(*world.getAssets().get(GameAssets::COLLISION));
    walkSound.setBuffer(*world.getAssets().get(GameAssets::WALK_SOUND));
    walkSound.setVolume(50);
    heartBeatSound.setBuffer(*world.getAssets().get(GameAssets::HEART_BEAT_SOUND));
    heartBeatSound.setVolume(25);
    heartBeatSound.setPitch(1.2);

    playerShader = world.getAssets().get(GameAssets::PLAYER_SHADER);

    setAnimationSprite(&sprite);
    msBetweenFrames = 100.0f;
}

sf::Vector2f Player::getRenderPosition() const {
    return renderPosition;
}

void Player::move(std::optional<Direction> direction) {
    inputDir = direction;
}

void Player::tick(float delta) {
    timeSinceLastHeartBeat += delta;
    if (timeSinceLastHeartBeat >= heartBeatDelay) {
        heartBeatSound.play();
        timeSinceLastHeartBeat = 0;
    }

    last_delta = delta;

	if(lastCollision > std::chrono::system_clock::now() - std::chrono::milliseconds(500))
		return;

	bool moving = position != destination;
    bool rotating = currentDir != destinationDir;

    renderPosition = (sf::Vector2f) position;
    if (moving) {
        runAnimation(delta);

        actionProgress += (delta / 1000) * movingSpeed;

        if (actionProgress > 1) {
            walkSound.stop();
            sf::Vector2i oldPos = position;
            position = destination;
			renderPosition = (sf::Vector2f) position;
            world.moveEntity(oldPos, this);
            actionProgress = 0;
        } else {
            renderPosition = (sf::Vector2f) position + sf::Vector2f(destination - position) * actionProgress;
        }
    } else if (rotating) {
		if(inputDir.has_value() && inputDir.value() != destinationDir) {
			currentDir = destinationDir;
			destinationDir = inputDir.value();
			actionProgress = 0;
		} else {
			actionProgress += (delta / 1000) * rotationSpeed;

			if (actionProgress > 1) {
				currentDir = destinationDir;
				actionProgress = 0;
			}
		}
    } else if (inputDir.has_value()) {
		if(inputDir.value() == currentDir) {
            destination = position + directionToUnitVector(inputDir.value());
            if (world.tileOccupied(destination, this) || lockMovement) {
                destination = position;
				if(!lockMovement) {
					collisionSound.play();
					lastCollision = std::chrono::system_clock::now();
				}
            } else {
                walkSound.setPitch(1.5 + ((rand() % 11) / 10));
                walkSound.play();
            }
        } else
			destinationDir = inputDir.value();

        frames.clear();
        switch (inputDir.value()) {
            case NORTH:
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_BACK_WALK_1));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_BACK_WALK_2));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_BACK_WALK_3));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_BACK_WALK_4));
                break;
            case EAST:
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_RIGHT_WALK_1));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_RIGHT_WALK_2));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_RIGHT_WALK_3));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_RIGHT_WALK_4));
                break;
            case SOUTH:
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_FRONT_WALK_1));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_FRONT_WALK_2));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_FRONT_WALK_3));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_FRONT_WALK_4));
                break;
            case WEST:
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_LEFT_WALK_1));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_LEFT_WALK_2));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_LEFT_WALK_3));
                frames.push_back(world.getAssets().get(GameAssets::PLAYER_LEFT_WALK_4));
                break;
        };
        startAnimation();
    }
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    if (position == destination)
        sprite.setTexture(*textureMap.at(destinationDir), true);

    if(hit_animation_is_playing)
    {
        this->hit_animation_current += last_delta / 1000.f;

        if(hit_animation_max < this->hit_animation_current)
        {
            hit_animation_is_playing = false;
            hit_animation_current = 0.0f;
        }
    }

    if(hit_animation_is_playing)
    {
        float player_hit = std::min(1.0f, std::exp(-hit_animation_current) * (5.0f / 10.f) * ( 1.0f + std::cos(10.0f * hit_animation_current))/ hit_animation_current);
        playerShader->setUniform("hit_multiplier", player_hit);
    }
    else
    {
        playerShader->setUniform("hit_multiplier", 0.0f);
    }

	sprite.setPosition({renderPosition.x - 0.5f, -renderPosition.y - 1.0f});
	sprite.setScale({ 2.0f / sprite.getTexture()->getSize().x, 2.0f / sprite.getTexture()->getSize().y });
	target.draw(sprite, playerShader);
}

void Player::setLockMovement(bool lockMovement) {
    Player::lockMovement = lockMovement;
}

bool Player::isBlocking(sf::Vector2i vec) {
    return vec == position || vec == destination;
}

int Player::getZOrder() const {
	return -1;
}

bool Player::isLockMovement() const {
    return lockMovement;
}

void Player::interact() {
	if(lastInteract > std::chrono::system_clock::now() - std::chrono::milliseconds(500))
		return;

	for(Entity* entity : world.getEntitiesAt(position + directionToUnitVector(currentDir)))
		if(Interactable* interactable = dynamic_cast<Interactable*>(entity))
		{
			if(!interactable->activate())
				continue;
			lastInteract = std::chrono::system_clock::now();
			interactSound.play();
			return;
		}

	lastInteract = std::chrono::system_clock::now();
	noInteractSound.play();
}

void Player::teleport(sf::Vector2i newPos) {
	if(newPos == position)
		return;

	sf::Vector2i oldPos = position;
	position = newPos;
	destination = newPos;
	renderPosition = (sf::Vector2f) position;
	world.moveEntity(oldPos, this);
}

void Player::setHeartBeatDelay(float delay) {
    heartBeatDelay = delay;
}

float Player::getHeartBeatDelay() {
    return heartBeatDelay;
}

void Player::animateHit() {
    hit_animation_is_playing = true;
    hit_animation_current = 0.0f;
}