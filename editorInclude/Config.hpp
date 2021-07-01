#ifndef CONFIG_HPP
#define CONFIG_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
	#include <SDL_image.h>
#else // This works for Mac
	#include <SDL_image.h>
    #include <SDL.h>
#endif

// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

const int CHARACTER_WIDTH {128};
const int CHARACTER_HEIGHT {128};

const int WINDOW_WIDTH {128};
const int WINDOW_HEIGHT {128};

enum IMG_STATE {
    FILE_COL = 0,
    FILE_ROW,
    SPRITE_WIDTH,
    SPRITE_HEIGHT,
    SPRITE_LAG
};

enum IMG_FILES {
	CHAR_IDLE_SPRITE_ID = 0,
	CHAR_WALK_SPRITE_ID,
	CHAR_JUMP_SPRITE_ID,
	CHAR_FALL_SPRITE_ID,
	CHAR_HIT_SPRITE_ID,
	ENEMY_WALK_SPRITE_ID,
	ENEMY_IDLE_SPRITE_ID,
	ENEMY_RUN_SPRITE_ID,
	ENEMY_HIT_SPRITE_ID,
	BACKGROUND_IMG_FILE_ID
};
const int SPRITE_INFO_NUM {5};

// ===================== player ====================== //
const char* const CHAR_IDLE_SPRITE = "../assets/images/character/Idle (32x32).png";
const int CHAR_IDLE_IMG_INFO[SPRITE_INFO_NUM] = {10,0,32,32,5};

const char* const CHAR_WALK_SPRITE = "../assets/images/character/Walk (32x32).png";
const int CHAR_WALK_IMG_INFO[SPRITE_INFO_NUM] = {11,0,32,32,5};

const char* const CHAR_JUMP_SPRITE = "../assets/images/character/Jump (32x32).png";
const int CHAR_JUMP_IMG_INFO[SPRITE_INFO_NUM] = {0,0,32,32,1};

const char* const CHAR_FALL_SPRITE = "../assets/images/character/Fall (32x32).png";
const int CHAR_FALL_IMG_INFO[SPRITE_INFO_NUM] = {0,0,32,32,1};

const char* const CHAR_HIT_SPRITE  = "../assets/images/character/Hit (32x32).png";
const int CHAR_HIT_IMG_INFO[SPRITE_INFO_NUM] = {6,0,32,32,3};

// ==================== enemy 1 ======================= //
const char* const ENEMY_WALK_SPRITE = "../assets/images/enemy1/Walk (36x30).png";
const int ENEMY_WALK_IMG_INFO[SPRITE_INFO_NUM] = {15,0,36,30,6};

const char* const ENEMY_IDLE_SPRITE = "../assets/images/enemy1/Idle (36x30).png";
const int ENEMY_IDLE_IMG_INFO[SPRITE_INFO_NUM] = {8,0,36,30,3};

const char* const ENEMY_RUN_SPRITE = "../assets/images/enemy1/Attack (36x30).png";
const int ENEMY_RUN_IMG_INFO[SPRITE_INFO_NUM] = {11,0,36,30,5};

const char* const ENEMY_HIT_SPRITE = "../assets/images/enemy1/Hit (36x30).png";
const int ENEMY_HIT_IMG_INFO[SPRITE_INFO_NUM] = {4,0,36,30,3};


const char *const BACKGROUND_IMG_FILE = "./../assets/images/background.png";
const int STILL_SPRITE_INFO[SPRITE_INFO_NUM] = {-1,-1,-1,-1,-1};

#endif