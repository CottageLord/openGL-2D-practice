/**
 * @file Sprite.cpp
 * @brief  This file contains the basic functions to create, update and draw sprite.
 * 
 * Sprite supports detecting the current orientation and
 * set moving direction functions for characters.
 */ 
#include "Sprite.hpp"

Sprite::Sprite() {
}

Sprite::Sprite(const char *const imgFilePath, SDL_Renderer* renderer, const int spriteInfo[SPRITE_INFO_NUM]) {
    this->LoadImage(imgFilePath, renderer, spriteInfo);
    spriteLagCount = 0;
    frameX = 0;
    frameY = 0;
    xPos = 0;
    yPos = 0;
}

Sprite::~Sprite() {
// TODO: Make sure spritesheet and m_texture are destroyed
// but is this the right place?
    SDL_FreeSurface(m_spriteSheet);
    m_spriteSheet = nullptr;
    SDL_DestroyTexture(m_texture);
}

void Sprite::Update() {
    // skip dynamic update update for static image
    if(staticImage) return;
    // only update every certain updates
    if(spriteLagCount > spriteLag) {
        spriteLagCount = 0; 
        frameX++;
    }
    // proceed to next image
    if(frameX > sheetCol){
        frameX = 0;
        frameY++;
    }
    if (frameY > sheetRow) frameY = 0;

    m_src.x = frameX * spriteWidth;
    m_src.y = frameY * spriteHeight;
    m_src.w = spriteWidth;
    m_src.h = spriteHeight;

    m_dest.x = xPos;
    m_dest.y = yPos;
    m_dest.w = CHARACTER_WIDTH;
    m_dest.h = CHARACTER_HEIGHT;

    spriteLagCount++;
}


void Sprite::Render(SDL_Renderer *ren) {
    SDL_RenderCopy(ren, m_texture, &m_src, &m_dest);
}


void Sprite::LoadImage(std::string filePath, SDL_Renderer *ren, const int spriteInfo[SPRITE_INFO_NUM]) {
    m_spriteSheet = IMG_Load(filePath.c_str());
    if (nullptr == m_spriteSheet) {
        SDL_Log("Failed to allocate surface");
    } else {
        SDL_Log("Allocated a bunch of memory to create identical game character");
        m_texture = SDL_CreateTextureFromSurface(ren, m_spriteSheet);
    }
    sheetCol = spriteInfo[FILE_COL];
    sheetRow = spriteInfo[FILE_ROW];
    spriteWidth = spriteInfo[SPRITE_WIDTH];
    spriteHeight = spriteInfo[SPRITE_HEIGHT];
    spriteLag = spriteInfo[SPRITE_LAG];
    if (sheetCol < 0 && sheetRow < 0) staticImage = true;
    else staticImage = false;
}

void Sprite::ResetFrame() {
    frameY = 0;
}

