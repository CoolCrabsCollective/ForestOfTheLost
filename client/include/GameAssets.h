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

#ifndef ASSET
#define ASSET(TYPE, NAME, CONSTRUCTOR) extern const TYPE NAME;
#endif

namespace GameAssets {
	extern std::vector<const wiz::AssetBase*> ALL;

	ASSET(wiz::MusicAsset, GREENLIFE, ("music/greenlife.ogg"))
	ASSET(wiz::SoundAsset, JUMP, ("sfx/jump.ogg"))
	ASSET(wiz::FontAsset, SANS_TTF, ("font/sans.ttf"))

	ASSET(wiz::TextureAsset, PLAYER, ("gfx/player.png"))
	ASSET(wiz::TextureAsset, BACKGROUND, ("gfx/background.jpg"))
	ASSET(wiz::TextureAsset, WHITE_PIXEL, ("gfx/white_pixel.png"))
	ASSET(wiz::TextureAsset, LOGO, ("gfx/logo.png"))

	ASSET(wiz::TextureAsset, SPOOKY_EYES, ("gfx/spooky_face.png"))

	ASSET(wiz::TextureAsset, HEART, ("gfx/heart.png"))
    ASSET(wiz::TextureAsset, ITEM_TEDDY, ("gfx/teddy_bear.png"))

    ASSET(wiz::TextureAsset, DIALOG_BOX, ("gfx/dialog_box.png"))

	ASSET(ShaderAsset, SPOOKY_SHADER, ("shaders/spooky.vs", "shaders/spooky.fs"))
	ASSET(ShaderAsset, EYES_SHADER, ("shaders/eyes.vs", "shaders/eyes.fs"))

    // Terrain
	ASSET(wiz::TextureAsset, GRASS_TERRAIN, ("gfx/terrain/grass.png"))
	ASSET(wiz::TextureAsset, WATER_TERRAIN, ("gfx/terrain/water.png"))
	ASSET(wiz::TextureAsset, SAND_TERRAIN, ("gfx/terrain/sand.png"))

    // Hiding Spots
    ASSET(wiz::TextureAsset, HIDING_SPOT, ("gfx/bush.png"))

	// Tree
    ASSET(wiz::TextureAsset, ALIVE_TREE, ("gfx/tree/alive.png"))
	ASSET(wiz::TextureAsset, DEAD_TREE, ("gfx/tree/dead.png"))
	ASSET(wiz::TextureAsset, THICK_DEAD_TREE, ("gfx/tree/thick_dead.png"))

    // Monsters
    ASSET(wiz::TextureAsset, BAT, ("gfx/bat2.png"))

    // Player
	ASSET(wiz::TextureAsset, PLAYER_BACK, ("gfx/player/back.png"))
	ASSET(wiz::TextureAsset, PLAYER_FRONT, ("gfx/player/front.png"))
	ASSET(wiz::TextureAsset, PLAYER_LEFT, ("gfx/player/left.png"))
	ASSET(wiz::TextureAsset, PLAYER_RIGHT, ("gfx/player/right.png"))

    // EndGoal
    ASSET(wiz::TextureAsset, END_GOAL, ("gfx/end_goal.png"))
}


#endif //GAMETEMPLATE_GAMEASSETS_H
