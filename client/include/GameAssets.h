//
// Created by Alexander Winter on 2022-02-13.
//

#ifndef GAMETEMPLATE_GAMEASSETS_H
#define GAMETEMPLATE_GAMEASSETS_H

#include "WIZ/asset/MusicAsset.h"
#include "WIZ/asset/SoundAsset.h"
#include "WIZ/asset/FontAsset.h"
#include "WIZ/asset/TextureAsset.h"
#include "ShaderAsset.h"
#include "TextAsset.h"

#ifndef ASSET
#define ASSET(TYPE, NAME, CONSTRUCTOR) extern const TYPE NAME;
#endif

namespace GameAssets {
	extern std::vector<const wiz::AssetBase*> ALL;

	// Music
	ASSET(wiz::MusicAsset, SUSPICIOUS_FOREST_MUSIC, ("music/suspicious_forest.ogg"))

	// Sounds
	ASSET(wiz::SoundAsset, COLLISION, ("sfx/collision.ogg"))
	ASSET(wiz::SoundAsset, INTERACT, ("sfx/interact.ogg"))
	ASSET(wiz::SoundAsset, NOINTERACT, ("sfx/nointeract.ogg"))
    ASSET(wiz::SoundAsset, WALK_SOUND, ("sfx/walk.ogg"))
    ASSET(wiz::SoundAsset, BUSH_SOUND, ("sfx/bush.ogg"))
    ASSET(wiz::SoundAsset, HEART_BEAT_SOUND, ("sfx/heart_beat.ogg"))
	ASSET(wiz::SoundAsset, AHHH_SOUND, ("sfx/ahhh.ogg"))

	ASSET(wiz::FontAsset, SANS_TTF, ("font/sans.ttf"))
	ASSET(wiz::FontAsset, VT323_TTF, ("font/VT323-Regular.ttf"))

	ASSET(wiz::TextureAsset, PLAYER, ("gfx/player.png"))
	ASSET(wiz::TextureAsset, WHITE_PIXEL, ("gfx/white_pixel.png"))

	// Eyes
	ASSET(wiz::TextureAsset, SPOOKY_EYES, ("gfx/spooky_face.png"))
    ASSET(wiz::TextureAsset, PACIFIC_EYES, ("gfx/pacific_eyes.png"))
    ASSET(wiz::TextureAsset, BEHOLDER_EYES, ("gfx/enemies/beholder_eyes.png"))
    ASSET(wiz::TextureAsset, SKULL_EYES, ("gfx/enemies/skull_eyes.png"))

	ASSET(wiz::TextureAsset, HEART, ("gfx/heart.png"))
    ASSET(wiz::TextureAsset, ITEM_TEDDY, ("gfx/teddy_bear.png"))
	ASSET(wiz::TextureAsset, ITEM_BALL, ("gfx/ball.png"))

    ASSET(wiz::TextureAsset, DIALOG_BOX, ("gfx/dialog_box.png"))

	ASSET(ShaderAsset, SPOOKY_SHADER, ("shaders/spooky.vs", "shaders/spooky.fs"))
	ASSET(ShaderAsset, EYES_SHADER, ("shaders/eyes.vs", "shaders/eyes.fs"))
	ASSET(ShaderAsset, PLAYER_SHADER, ("shaders/player.vs", "shaders/player.fs"))

	ASSET(TextAsset, CONTROLLER_DB, ("gamecontrollerdb.txt"))

    // Terrain
	ASSET(wiz::TextureAsset, SHORT_GRASS_TERRAIN, ("gfx/terrain/short_grass.png"))
	ASSET(wiz::TextureAsset, GRASS_TERRAIN, ("gfx/terrain/grass.png"))
	ASSET(wiz::TextureAsset, WATER_TERRAIN, ("gfx/terrain/water.png"))
	ASSET(wiz::TextureAsset, SAND_TERRAIN, ("gfx/terrain/sand.png"))

    // Hiding Spots
    ASSET(wiz::TextureAsset, BUSH, ("gfx/george_hw/bush.png"))
    ASSET(wiz::TextureAsset, BUSH2, ("gfx/george_hw/bush2.png"))

    ASSET(wiz::TextureAsset, WITHERED_BUSH, ("gfx/george_hw/withered.png"))
    ASSET(wiz::TextureAsset, WITHERED_BUSH2, ("gfx/george_hw/withered2.png"))

	// Tree
    ASSET(wiz::TextureAsset, ALIVE_TREE, ("gfx/tree/alive.png"))
	ASSET(wiz::TextureAsset, SQUIRREL_TREE, ("gfx/tree/squirrel_tree.png"))
	ASSET(wiz::TextureAsset, DEAD_TREE, ("gfx/tree/dead.png"))
	ASSET(wiz::TextureAsset, THICK_DEAD_TREE, ("gfx/tree/thick_dead.png"))

    // Monsters
    ASSET(wiz::TextureAsset, BAT, ("gfx/bat2.png"))
    ASSET(wiz::TextureAsset, SNAKE, ("gfx/enemies/snake.png"))
    ASSET(wiz::TextureAsset, SKULL, ("gfx/enemies/skull.png"))
    ASSET(wiz::TextureAsset, GROUND_HOG, ("gfx/marmotte.png"))
    ASSET(wiz::TextureAsset, WRAITH, ("gfx/wraith.png"))
    ASSET(wiz::TextureAsset, GHOUL, ("gfx/ghoul.png"))
    ASSET(wiz::TextureAsset, BEHOLDER, ("gfx/enemies/beholder.png"))
    ASSET(wiz::TextureAsset, HOT_GHOST_MOM, ("gfx/ghost_mom.png"))

    // Misc
    ASSET(wiz::TextureAsset, INVISIBLE, ("gfx/invisible.png"))

    // Player
	ASSET(wiz::TextureAsset, PLAYER_BACK, ("gfx/player/back.png"))
	ASSET(wiz::TextureAsset, PLAYER_FRONT, ("gfx/player/front.png"))
	ASSET(wiz::TextureAsset, PLAYER_LEFT, ("gfx/player/left.png"))
	ASSET(wiz::TextureAsset, PLAYER_RIGHT, ("gfx/player/right.png"))
	ASSET(wiz::TextureAsset, PLAYER_DETECTIVE, ("gfx/player/magnifying_glass.png"))

    // Player Forward Walk Animation
    ASSET(wiz::TextureAsset, PLAYER_FRONT_WALK_1, ("gfx/player/animation/front/walk_front_1.png"))
    ASSET(wiz::TextureAsset, PLAYER_FRONT_WALK_2, ("gfx/player/animation/front/walk_front_2.png"))
    ASSET(wiz::TextureAsset, PLAYER_FRONT_WALK_3, ("gfx/player/animation/front/walk_front_3.png"))
    ASSET(wiz::TextureAsset, PLAYER_FRONT_WALK_4, ("gfx/player/animation/front/walk_front_4.png"))
    // Player Left Walk Animation
    ASSET(wiz::TextureAsset, PLAYER_LEFT_WALK_1, ("gfx/player/animation/left/walk_left_1.png"))
    ASSET(wiz::TextureAsset, PLAYER_LEFT_WALK_2, ("gfx/player/animation/left/walk_left_2.png"))
    ASSET(wiz::TextureAsset, PLAYER_LEFT_WALK_3, ("gfx/player/animation/left/walk_left_3.png"))
    ASSET(wiz::TextureAsset, PLAYER_LEFT_WALK_4, ("gfx/player/animation/left/walk_left_4.png"))
    // Player Right Walk Animation
    ASSET(wiz::TextureAsset, PLAYER_RIGHT_WALK_1, ("gfx/player/animation/right/walk_right_1.png"))
    ASSET(wiz::TextureAsset, PLAYER_RIGHT_WALK_2, ("gfx/player/animation/right/walk_right_2.png"))
    ASSET(wiz::TextureAsset, PLAYER_RIGHT_WALK_3, ("gfx/player/animation/right/walk_right_3.png"))
    ASSET(wiz::TextureAsset, PLAYER_RIGHT_WALK_4, ("gfx/player/animation/right/walk_right_4.png"))
    // Player BACK Walk Animation
    ASSET(wiz::TextureAsset, PLAYER_BACK_WALK_1, ("gfx/player/animation/back/walk_back_1.png"))
    ASSET(wiz::TextureAsset, PLAYER_BACK_WALK_2, ("gfx/player/animation/back/walk_back_2.png"))
    ASSET(wiz::TextureAsset, PLAYER_BACK_WALK_3, ("gfx/player/animation/back/walk_back_3.png"))
    ASSET(wiz::TextureAsset, PLAYER_BACK_WALK_4, ("gfx/player/animation/back/walk_back_4.png"))

	// Teddy kid
	ASSET(wiz::TextureAsset, TEDDY_KID_BACK, ("gfx/npcs/teddy_kid/back.png"))
	ASSET(wiz::TextureAsset, TEDDY_KID_FRONT, ("gfx/npcs/teddy_kid/front.png"))
	ASSET(wiz::TextureAsset, TEDDY_KID_LEFT, ("gfx/npcs/teddy_kid/left.png"))
	ASSET(wiz::TextureAsset, TEDDY_KID_RIGHT, ("gfx/npcs/teddy_kid/right.png"))

    // Crying girl
    ASSET(wiz::TextureAsset, CRYING_GIRL_BACK, ("gfx/npcs/crying_girl/back.png"))
    ASSET(wiz::TextureAsset, CRYING_GIRL_FRONT, ("gfx/npcs/crying_girl/front.png"))
    ASSET(wiz::TextureAsset, CRYING_GIRL_LEFT, ("gfx/npcs/crying_girl/left.png"))
    ASSET(wiz::TextureAsset, CRYING_GIRL_RIGHT, ("gfx/npcs/crying_girl/right.png"))

    ASSET(wiz::TextureAsset, LILY, ("gfx/npcs/crying_girl/polaroid.png"))

	// Monster kid
	ASSET(wiz::TextureAsset, MONSTER_KID_BACK, ("gfx/npcs/monster_kid/back.png"))
	ASSET(wiz::TextureAsset, MONSTER_KID_FRONT, ("gfx/npcs/monster_kid/front.png"))
	ASSET(wiz::TextureAsset, MONSTER_KID_LEFT, ("gfx/npcs/monster_kid/left.png"))
	ASSET(wiz::TextureAsset, MONSTER_KID_RIGHT, ("gfx/npcs/monster_kid/right.png"))

	ASSET(wiz::TextureAsset, MONSTER_KID_MONSTER, ("gfx/npcs/monster_kid/monster.png"))

    // EndGoal
    ASSET(wiz::TextureAsset, END_GOAL, ("gfx/end_goal.png"))

    ASSET(wiz::TextureAsset, OFFICE, ("gfx/background.png"))
}


#endif //GAMETEMPLATE_GAMEASSETS_H
