#pragma once

#include <SDL2/SDL.h>

#include "structs.hpp"
#include "camrea.hpp"

//'extern' is for global varriables
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern int pixelsPerGamePixels;
extern bool debugMode;
extern int loopNumber;
extern double currentFPS;
extern string operatingSystem;
extern vector<double> largestFPSlist;
extern bool updateRenderingOnResize;
extern bool muted;
extern Audio audio;
extern Camrea camrea;
extern rectangle screenSize;
