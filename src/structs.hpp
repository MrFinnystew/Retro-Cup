#pragma once

//
//  structs.cpp
//  Retro Cup
//
//  Created by Yu-El Cheong on 3/19/26.
//
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using
std::string,
std::vector;

typedef struct COLOR {
    int red;
    int green;
    int blue;
    int transparency;
} COLOR;

typedef struct Item{
    string itemName;
    int x;
    int y;
} Item;

typedef struct Sprite {
    int spriteWidth;
    int spriteHeight;
    string pathToFile;
    string fileName;
    string uiFileName;
    SDL_Texture* Texture;
    SDL_Rect rect;
} Sprite;

typedef struct MoveAnimation {
    SDL_Texture* frame1;
    SDL_Texture* frame2;
    SDL_Texture* frame3;
    SDL_Texture* frame4;
    SDL_Texture* frame5;
    bool frame1IsLoaded;
    bool frame2IsLoaded;
    bool frame3IsLoaded;
    bool frame4IsLoaded;
    bool frame5IsLoaded;
} MoveAnimation;

typedef struct cardAnimation {
    SDL_Texture* frame1;
    SDL_Texture* frame2;
    SDL_Texture* frame3;
    SDL_Texture* frame4;
    SDL_Texture* frame5;
    SDL_Texture* frame6;
    bool frame1IsLoaded;
    bool frame2IsLoaded;
    bool frame3IsLoaded;
    bool frame4IsLoaded;
    bool frame5IsLoaded;
    bool frame6IsLoaded;
} cardAnimation;

typedef struct penaltyCardFrames {
    cardAnimation red;
    cardAnimation yellow;
    cardAnimation white;
    cardAnimation blue;
    bool redIsLoaded;
    bool yellowIsLoaded;
    bool whiteIsLoaded;
    bool blueIsLoaded;
} penaltyCardFrames;

typedef struct Animation {
    MoveAnimation walk;
    MoveAnimation run;
    penaltyCardFrames card;
    bool walkIsLoaded;
    bool runIsLoaded;
    bool cardsAreLoaded;
} Animation;

typedef struct humanSprite {
    SDL_Texture* Texture;
    bool normalTextureIsLoaded;
    bool allAnimationsAreLoaded;
    SDL_Rect rect;
    bool yellowCard;
    bool redCard;
    bool blueCard;
    Animation animaion;
} humanInfo;

typedef struct ballSprite {
    SDL_Texture* texture;
    bool textureIsLoaded;
    SDL_Rect rect;
} ballSprite;

typedef struct individualFieldTexture {
    SDL_Texture* normal;
    bool normalIsLoaded;
    SDL_Texture* snow;
    bool snowIsLoaded;
    SDL_Texture* rain;
    bool rainIsLoaded;
} individualFieldTexture;

typedef struct fieldTextures {
    individualFieldTexture normal;
    bool normalIsLoaded;
    individualFieldTexture debug;
    bool debugIsLoaded;
} fieldTextures;

typedef struct fieldSprite {
    string spriteName;
    bool allFieldsAreLoaded;
    
    SDL_Rect rect;
    fieldTextures textures;
} fieldSprite;

typedef struct rectangle {
    int width;
    int height;
    int gameWidth;
    int gameHeight;
    int originalWidth;
    int originalHeight;
    int pixels;
} rectangle;
