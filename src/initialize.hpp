#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <limits>
#include <cmath>
#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <cstdlib>

#include "../audio/Audio Engine.hpp"
#include "color text.hpp"

#include "structs.hpp"
#include "enums.hpp"
#include "globals.hpp"
#include "camrea.hpp"
#include "printing.hpp"
#include "functions.hpp"

void init() {
    renderer = nullptr;
    window = nullptr;
    pixelsPerGamePixels = 0;
    debugMode = true;
    loopNumber = 0;
    currentFPS = 0.0;
    largestFPSlist = {};
    updateRenderingOnResize = true;
    muted = false;
    mute();
    printBold("Initializing...\n");
    
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  /* Pixel-perfect rendering */
    
    /* Width: 444, Height: 690 (Height is automaticly caculated by the function) */
    int wantedWidthPixels = 444;
    screenSize = getScreenSize(wantedWidthPixels);
    pixelsPerGamePixels = screenSize.pixels;
    
    printBold("Screen Info:");
    printInfo("Screen Size: " + toString(screenSize.originalWidth) + " x " + toString(screenSize.originalHeight) + "\n");
    printInfo("Window Size: " + toString(screenSize.width) + " x " + toString(screenSize.height) + "\n");
    printInfo("Game Size:   " + toString(screenSize.gameWidth) + " x " + toString(screenSize.gameHeight) + "\n");
    printInfo("Pixels: " + toString(screenSize.pixels) + "\n");
    
    string windowName = "Retro Cup | vAlpha 0.1.2 | Last updated: 3/1/2026";
    
    window = SDL_CreateWindow(windowName.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screenSize.width, screenSize.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); /* SDL_RENDERER_ACCELERATED */
    
    /*-----------------------------------------------
     -----------------Loaded Window-----------------
     -----------------------------------------------*/
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  /* Add this BEFORE creating textures */
    
    camrea.x = 0;
    camrea.y = 0;
    camrea.zoom = 1;
    
    
    /*
     Audio stuff:
     */
    mute();
    audio.load("debugMusic", "/Users/yec/Documents/Retro Cup/Retro Cup/Audio/Sounds/Arrow (Instrumental).mp3");
    audio.setLoop("debugMusic", true);
    audio.setVolume("debugMusic", 1.0f);
    audio.playLoaded("debugMusic");
    
#if defined(__APPLE__)
    operatingSystem = "Apple";
#elif defined(__linux__)
    operatingSystem = "Linux";
#elif defined(_WIN32)
    operatingSystem = "Windows";
#else
    error("Operating System not allowed.\nError\n\nPlease Contact: yuel.cheong@gmail.com");
    operatingSystem = "Not allowed";
    return -1;
#endif
    printInfo(operatingSystem+"\n");
}
