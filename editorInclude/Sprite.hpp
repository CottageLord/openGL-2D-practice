/**
 * @file Sprite.hpp
 * @brief This file contains the basic functions to create, update and draw sprite.
 * 
 * Sprite supports detecting the current orientation and
 * set moving direction functions for characters.
 */ 
#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <iostream>
#include "Config.hpp"

/**
 * @brief Sprite supports detecting the current orientation and set moving direction functions for characters.
 */
class Sprite {
public:

    /**
     * Constructor
     */
    Sprite();

    /**
     * Constructor
     * @param imgFilePath The file name of the source image file.
     * @param renderer Reference to SDL_Renderer.
     * @param spriteInfo Stores width and height of the sprite in the source file and in the game window. 
     */
    Sprite(const char *const imgFilePath, SDL_Renderer* renderer, const int spriteInfo[SPRITE_INFO_NUM]);

    /**
     * Destructor
     */
    ~Sprite();

    /**
     * Update the position of this sprite.
     */
    void Update();

    /**
     * @brief Render something to the active viewport.
     * @param ren Reference to SDL renderer.
     */
    void Render(SDL_Renderer *ren);

    /**
     * Set the frame this sprite's animation to 0;
     */
    void ResetFrame();

    /**
     * Load image file and change the sprite sheet.
     * @param filePath The file name of the image file.
     * @param ren Reference to SDL renderer.
     * @param spriteInfo Stores width and height of the sprite in the source file and in the game window.
     */
    void LoadImage(std::string filePath, SDL_Renderer *ren, const int spriteInfo[SPRITE_INFO_NUM]);


private:
    /// The x location of the sprite's upper left corner in the game.
    int xPos;
    /// The y location of the sprite's upper left corner in the game.
    int yPos;

    /// Whether the sprite image is static.
    bool staticImage;

    /// For slowing down sprite display.
    int spriteLag; 
    /// For slowing down sprite display.
    int spriteLagCount;

    /// The x position of the image should be displayed
    int frameX;
    /// The y position of the image should be displayed
    int frameY;
    // sprite file info

    /// The number of columns of the image on sprite sheet
    int sheetCol;

    /// The number of rows of the image on sprite sheet
    int sheetRow;

    /// The width of the sprite
    int spriteWidth;

    /// The height of the sprite
    int spriteHeight;

    /// A structure that contains a collection of pixels of the sprite sheet used in software blitting.
    SDL_Surface *m_spriteSheet;

    /// A structure that contains an efficient, driver-specific representation of pixel data.
    SDL_Texture *m_texture;

    /// The box area contains the source image area
    SDL_Rect m_src;

    /// The box area that will contain the generated sprite area
    SDL_Rect m_dest;
};

#endif
