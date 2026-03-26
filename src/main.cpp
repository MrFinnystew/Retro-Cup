/* Retro Cup Main.cpp
 * ----------------------------- Version information: -----------------------------------------
 
                                      Versions:
 vBeta011
 vBeta012
 vBeta013 (Current version)
 
-----------------------------Last updated: Sat Feb 14 --------------------------------------

Notes are set up like C++
"{

 }"
 This is used to define a section
 
 "def"
 Used when defining something that will be used over and over in this code.
 
 Visuals {
 SDL2
 }
 
 notesForYu-El {
     /Users/yec/Library/Developer/Xcode/DerivedData/Retro_Cup-epucvnkixjmotphfdzpnvcotyiyg/Build/Products/Debug/Retro Cup
 }
 
 Notation {
    PascelCase
    and
    camelCase
 }
 
 READ THIS BEFORE CODING ON THIS DOCUMENT {
    def Sprite{
        Sprite stands for a thing on the screen, like the field, the player, or the ref.
    }
    info {
        We are using SDL2 for displaying, and we are still deciding what to use for sound.
        All comments are with multiple-line comments.
    }
 }
 */

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
#include "renderer.hpp"
#include "printing.hpp"
#include "functions.hpp"

#include "initialize.hpp"

/* Are using these: */
using
std::cout,
std::cin,
std::string,
std::endl,
std::vector,
std::ctime;

/*-----------------------------------------------------------------
  -----------------------------Classes-----------------------------
  -----------------------------------------------------------------*/
class human {
public:
    humanInfo info;
    animationType currentShownFrame = NONE;
    string spriteName;
    int worldX = 0;
    int worldY = 0;
    
    human(string importedSpriteName) {
        spriteName = importedSpriteName;
        initTextures();
        alphaGoTo(0, 0);
    }
    
    void initTextures() {
        info.Texture = nullptr;
        info.animaion.walk.frame1 = nullptr;
        info.animaion.walk.frame2 = nullptr;
        info.animaion.walk.frame3 = nullptr;
        info.animaion.walk.frame4 = nullptr;
        info.animaion.walk.frame5 = nullptr;
        info.animaion.run.frame1 = nullptr;
        info.animaion.run.frame2 = nullptr;
        info.animaion.run.frame3 = nullptr;
        info.animaion.run.frame4 = nullptr;
        info.animaion.run.frame5 = nullptr;
        info.animaion.card.red.frame1 = nullptr;
        info.animaion.card.red.frame2 = nullptr;
        info.animaion.card.red.frame3 = nullptr;
        info.animaion.card.red.frame4 = nullptr;
        info.animaion.card.red.frame5 = nullptr;
        info.animaion.card.red.frame6 = nullptr;
        info.animaion.card.yellow.frame1 = nullptr;
        info.animaion.card.yellow.frame2 = nullptr;
        info.animaion.card.yellow.frame3 = nullptr;
        info.animaion.card.yellow.frame4 = nullptr;
        info.animaion.card.yellow.frame5 = nullptr;
        info.animaion.card.yellow.frame6 = nullptr;
        info.animaion.card.white.frame1 = nullptr;
        info.animaion.card.white.frame2 = nullptr;
        info.animaion.card.white.frame3 = nullptr;
        info.animaion.card.white.frame4 = nullptr;
        info.animaion.card.white.frame5 = nullptr;
        info.animaion.card.white.frame6 = nullptr;
        info.animaion.card.blue.frame1 = nullptr;
        info.animaion.card.blue.frame2 = nullptr;
        info.animaion.card.blue.frame3 = nullptr;
        info.animaion.card.blue.frame4 = nullptr;
        info.animaion.card.blue.frame5 = nullptr;
        info.animaion.card.blue.frame6 = nullptr;
    }
    
    /*
     ------------------------------------------------------------------------------------------
     --------------------------------Loading animations----------------------------------------
     ------------------------------------------------------------------------------------------
     */
    
    void loadAnimation(vector<string> filePaths, animationType AnimationType) {
        if (AnimationType == NONE) {
            warrning("Warrning AnimaionType was set to NONE (void loadAnimaion)");
        }
        else if (AnimationType == NORMAL) {
            string currentFilePath = filePaths[0];
            info.Texture = loadTexture(currentFilePath);
            info.normalTextureIsLoaded = true;
        }
        else if (AnimationType == RUN) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.run.frame1 = loadTexture(currentFilePath);
            info.animaion.run.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.run.frame2 = loadTexture(currentFilePath);
            info.animaion.run.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.run.frame3 = loadTexture(currentFilePath);
            info.animaion.run.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.run.frame4 = loadTexture(currentFilePath);
            info.animaion.run.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.run.frame5 = loadTexture(currentFilePath);
            info.animaion.run.frame5IsLoaded = true;
            
            info.animaion.runIsLoaded = true;
            
            if (info.animaion.walkIsLoaded && info.animaion.cardsAreLoaded) {
                info.allAnimationsAreLoaded = true;
            }
        }
        else if (AnimationType == WALK) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.walk.frame1 = loadTexture(currentFilePath);
            info.animaion.walk.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.walk.frame2 = loadTexture(currentFilePath);
            info.animaion.walk.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.walk.frame3 = loadTexture(currentFilePath);
            info.animaion.walk.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.walk.frame4 = loadTexture(currentFilePath);
            info.animaion.walk.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.walk.frame5 = loadTexture(currentFilePath);
            info.animaion.walk.frame5IsLoaded = true;
            
            info.animaion.walkIsLoaded = true;
            
            if (info.animaion.runIsLoaded && info.animaion.cardsAreLoaded) {
                info.allAnimationsAreLoaded = true;
            }
        }
        else if (AnimationType == CARD_RED) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.red.frame1 = loadTexture(currentFilePath);
            info.animaion.card.red.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.red.frame2 = loadTexture(currentFilePath);
            info.animaion.card.red.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.red.frame3 = loadTexture(currentFilePath);
            info.animaion.card.red.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.red.frame4 = loadTexture(currentFilePath);
            info.animaion.card.red.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.red.frame5 = loadTexture(currentFilePath);
            info.animaion.card.red.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.red.frame6 = loadTexture(currentFilePath);
            info.animaion.card.red.frame6IsLoaded = true;
            
            info.animaion.card.redIsLoaded = true;
            
            if (info.animaion.card.blueIsLoaded && info.animaion.card.whiteIsLoaded && info.animaion.card.yellowIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        else if (AnimationType == CARD_YELLOW) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.yellow.frame1 = loadTexture(currentFilePath);
            info.animaion.card.yellow.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.yellow.frame2 = loadTexture(currentFilePath);
            info.animaion.card.yellow.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.yellow.frame3 = loadTexture(currentFilePath);
            info.animaion.card.yellow.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.yellow.frame4 = loadTexture(currentFilePath);
            info.animaion.card.yellow.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.yellow.frame5 = loadTexture(currentFilePath);
            info.animaion.card.yellow.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.yellow.frame6 = loadTexture(currentFilePath);
            info.animaion.card.yellow.frame6IsLoaded = true;
            
            info.animaion.card.yellowIsLoaded = true;
            
            if (info.animaion.card.blueIsLoaded && info.animaion.card.whiteIsLoaded && info.animaion.card.redIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        else if (AnimationType == CARD_BLUE) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.blue.frame1 = loadTexture(currentFilePath);
            info.animaion.card.blue.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.blue.frame2 = loadTexture(currentFilePath);
            info.animaion.card.blue.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.blue.frame3 = loadTexture(currentFilePath);
            info.animaion.card.blue.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.blue.frame4 = loadTexture(currentFilePath);
            info.animaion.card.blue.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.blue.frame5 = loadTexture(currentFilePath);
            info.animaion.card.blue.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.blue.frame6 = loadTexture(currentFilePath);
            info.animaion.card.blue.frame6IsLoaded = true;
            
            info.animaion.card.blueIsLoaded = true;
            
            if (info.animaion.card.yellowIsLoaded && info.animaion.card.whiteIsLoaded && info.animaion.card.redIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        else if (AnimationType == CARD_WHITE) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.white.frame1 = loadTexture(currentFilePath);
            info.animaion.card.white.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.white.frame2 = loadTexture(currentFilePath);
            info.animaion.card.white.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.white.frame3 = loadTexture(currentFilePath);
            info.animaion.card.white.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.white.frame4 = loadTexture(currentFilePath);
            info.animaion.card.white.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.white.frame5 = loadTexture(currentFilePath);
            info.animaion.card.white.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.white.frame6 = loadTexture(currentFilePath);
            info.animaion.card.white.frame6IsLoaded = true;
            
            info.animaion.card.whiteIsLoaded = true;
            
            if (info.animaion.card.yellowIsLoaded && info.animaion.card.blueIsLoaded && info.animaion.card.redIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        else {
            if (debugMode)
                error("Error not a valid type! (Tried to load animaion\n)");
        }
    }
    
    /*
     ------------------------------------------------------------------------------------------
     ----------------------------------Displaying Functions------------------------------------
     ------------------------------------------------------------------------------------------
     */
    
    void alphaDisplay(animationType type) {
        currentShownFrame = type;
        if (type == NONE){
            warrning("Warrning type was set to NONE (void alphaDisplay(animationType type))");
        }
        else if (type == NORMAL) {
            SDL_RenderCopy(renderer, info.Texture, NULL, &info.rect);
            currentShownFrame = NORMAL;
        }
        // Walking Frames
        else if (type == WALK_FRAME1) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame1, NULL, &info.rect);
                currentShownFrame = WALK_FRAME1;
            }
        }
        else if (type == WALK_FRAME2) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame2, NULL, &info.rect);
            }
        }
        else if (type == WALK_FRAME3) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame3, NULL, &info.rect);
            }
        }
        else if (type == WALK_FRAME4) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame4, NULL, &info.rect);
            }
        }
        else if (type == WALK_FRAME5) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame5, NULL, &info.rect);
            }
        }
        // Runing Frames
        else if (type == RUN_FRAME1) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame1, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME2) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame2, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME3) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame3, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME4) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame4, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME5) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame5, NULL, &info.rect);
            }
        }
        // Card Frames
        // Red Card
        else if (type == CARD_RED_FRAME1) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME2) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME3) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME4) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME5) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME6) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame6, NULL, &info.rect);
            }
        }
            // Yellow Card
        else if (type == CARD_YELLOW_FRAME1) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME2) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME3) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME4) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME5) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME6) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame6, NULL, &info.rect);
            }
        }
            // White Card
        else if (type == CARD_WHITE_FRAME1) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME2) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME3) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME4) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME5) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME6) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame6, NULL, &info.rect);
            }
        }
            // Blue Card
        else if (type == CARD_BLUE_FRAME1) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME2) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME3) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME4) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME5) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME6) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame6, NULL, &info.rect);
            }
        }
        else {
            if (debugMode)
                error("Error not a valid type! (Tried to display texture)\n");
        }
    }
    
    void display(animationType type) {
        resizeForFrame(type);
        currentShownFrame = type;
        if (type == NONE){
            warrning("Warrning type was set to NONE (void display)");
        }
        else if (type == NORMAL) {
            SDL_RenderCopy(renderer, info.Texture, NULL, &info.rect);
            currentShownFrame = NORMAL;
        }
        // Walking Frames
        else if (type == WALK_FRAME1) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame1, NULL, &info.rect);
                currentShownFrame = WALK_FRAME1;
            }
        }
        else if (type == WALK_FRAME2) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame2, NULL, &info.rect);
            }
        }
        else if (type == WALK_FRAME3) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame3, NULL, &info.rect);
            }
        }
        else if (type == WALK_FRAME4) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame4, NULL, &info.rect);
            }
        }
        else if (type == WALK_FRAME5) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.walk.frame5, NULL, &info.rect);
            }
        }
        // Runing Frames
        else if (type == RUN_FRAME1) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame1, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME2) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame2, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME3) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame3, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME4) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame4, NULL, &info.rect);
            }
        }
        else if (type == RUN_FRAME5) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.run.frame5, NULL, &info.rect);
            }
        }
        // Card Frames
        // Red Card
        else if (type == CARD_RED_FRAME1) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME2) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME3) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME4) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME5) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_RED_FRAME6) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.red.frame6, NULL, &info.rect);
            }
        }
            // Yellow Card
        else if (type == CARD_YELLOW_FRAME1) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME2) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME3) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME4) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME5) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_YELLOW_FRAME6) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.yellow.frame6, NULL, &info.rect);
            }
        }
            // White Card
        else if (type == CARD_WHITE_FRAME1) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME2) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME3) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME4) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME5) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_WHITE_FRAME6) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.white.frame6, NULL, &info.rect);
            }
        }
            // Blue Card
        else if (type == CARD_BLUE_FRAME1) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame1IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame1, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME2) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame2IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame2, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME3) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame3IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame3, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME4) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame4IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame4, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME5) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame5IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame5, NULL, &info.rect);
            }
        }
        else if (type == CARD_BLUE_FRAME6) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame6IsLoaded) {
                SDL_RenderCopy(renderer, info.animaion.card.blue.frame6, NULL, &info.rect);
            }
        }
        else {
            if (debugMode)
                error("Error not a valid type! (Tried to display texture)\n");
        }
    }
    
    /*
     ------------------------------------------------------------------------------------------
     ----------------------------------Unloading Functions-------------------------------------
     ------------------------------------------------------------------------------------------
     */
    
    ~human() {
        if (info.Texture) SDL_DestroyTexture(info.Texture);
        if (info.animaion.walk.frame1) SDL_DestroyTexture(info.animaion.walk.frame1);
        if (info.animaion.walk.frame2) SDL_DestroyTexture(info.animaion.walk.frame2);
        if (info.animaion.walk.frame3) SDL_DestroyTexture(info.animaion.walk.frame3);
        if (info.animaion.walk.frame4) SDL_DestroyTexture(info.animaion.walk.frame4);
        if (info.animaion.walk.frame5) SDL_DestroyTexture(info.animaion.walk.frame5);
        if (info.animaion.run.frame1) SDL_DestroyTexture(info.animaion.run.frame1);
        if (info.animaion.run.frame2) SDL_DestroyTexture(info.animaion.run.frame2);
        if (info.animaion.run.frame3) SDL_DestroyTexture(info.animaion.run.frame3);
        if (info.animaion.run.frame4) SDL_DestroyTexture(info.animaion.run.frame4);
        if (info.animaion.run.frame5) SDL_DestroyTexture(info.animaion.run.frame5);
        if (info.animaion.card.red.frame1) SDL_DestroyTexture(info.animaion.card.red.frame1);
        if (info.animaion.card.red.frame2) SDL_DestroyTexture(info.animaion.card.red.frame2);
        if (info.animaion.card.red.frame3) SDL_DestroyTexture(info.animaion.card.red.frame3);
        if (info.animaion.card.red.frame4) SDL_DestroyTexture(info.animaion.card.red.frame4);
        if (info.animaion.card.red.frame5) SDL_DestroyTexture(info.animaion.card.red.frame5);
        if (info.animaion.card.red.frame6) SDL_DestroyTexture(info.animaion.card.red.frame6);
        if (info.animaion.card.yellow.frame1) SDL_DestroyTexture(info.animaion.card.yellow.frame1);
        if (info.animaion.card.yellow.frame2) SDL_DestroyTexture(info.animaion.card.yellow.frame2);
        if (info.animaion.card.yellow.frame3) SDL_DestroyTexture(info.animaion.card.yellow.frame3);
        if (info.animaion.card.yellow.frame4) SDL_DestroyTexture(info.animaion.card.yellow.frame4);
        if (info.animaion.card.yellow.frame5) SDL_DestroyTexture(info.animaion.card.yellow.frame5);
        if (info.animaion.card.yellow.frame6) SDL_DestroyTexture(info.animaion.card.yellow.frame6);
        if (info.animaion.card.white.frame1) SDL_DestroyTexture(info.animaion.card.white.frame1);
        if (info.animaion.card.white.frame2) SDL_DestroyTexture(info.animaion.card.white.frame2);
        if (info.animaion.card.white.frame3) SDL_DestroyTexture(info.animaion.card.white.frame3);
        if (info.animaion.card.white.frame4) SDL_DestroyTexture(info.animaion.card.white.frame4);
        if (info.animaion.card.white.frame5) SDL_DestroyTexture(info.animaion.card.white.frame5);
        if (info.animaion.card.white.frame6) SDL_DestroyTexture(info.animaion.card.white.frame6);
        if (info.animaion.card.blue.frame1) SDL_DestroyTexture(info.animaion.card.blue.frame1);
        if (info.animaion.card.blue.frame2) SDL_DestroyTexture(info.animaion.card.blue.frame2);
        if (info.animaion.card.blue.frame3) SDL_DestroyTexture(info.animaion.card.blue.frame3);
        if (info.animaion.card.blue.frame4) SDL_DestroyTexture(info.animaion.card.blue.frame4);
        if (info.animaion.card.blue.frame5) SDL_DestroyTexture(info.animaion.card.blue.frame5);
        if (info.animaion.card.blue.frame6) SDL_DestroyTexture(info.animaion.card.blue.frame6);
    }
    
    void nextFrame() {
        resizeForFrame(currentShownFrame);
        if (currentShownFrame == NONE) {
            if (debugMode)
                error("Error! (Tried to show next frame)\n");
        }
        /* Walk */
        else if (currentShownFrame == WALK_FRAME1) {
            SDL_RenderCopy(renderer, info.animaion.walk.frame2, NULL, &info.rect);
            currentShownFrame = WALK_FRAME2;
        }
        else if (currentShownFrame == WALK_FRAME2) {
            SDL_RenderCopy(renderer, info.animaion.walk.frame3, NULL, &info.rect);
            currentShownFrame = WALK_FRAME3;
        }
        else if (currentShownFrame == WALK_FRAME3) {
            SDL_RenderCopy(renderer, info.animaion.walk.frame4, NULL, &info.rect);
            currentShownFrame = WALK_FRAME4;
        }
        else if (currentShownFrame == WALK_FRAME4) {
            SDL_RenderCopy(renderer, info.animaion.walk.frame5, NULL, &info.rect);
            currentShownFrame = WALK_FRAME5;
        }
        else if (currentShownFrame == WALK_FRAME5) {
            SDL_RenderCopy(renderer, info.animaion.walk.frame1, NULL, &info.rect);
            currentShownFrame = WALK_FRAME1;
        }
        /* Run */
        else if (currentShownFrame == RUN_FRAME1) {
            SDL_RenderCopy(renderer, info.animaion.run.frame2, NULL, &info.rect);
            currentShownFrame = WALK_FRAME2;
        }
        else if (currentShownFrame == RUN_FRAME2) {
            SDL_RenderCopy(renderer, info.animaion.run.frame3, NULL, &info.rect);
            currentShownFrame = WALK_FRAME3;
        }
        else if (currentShownFrame == RUN_FRAME3) {
            SDL_RenderCopy(renderer, info.animaion.run.frame4, NULL, &info.rect);
            currentShownFrame = WALK_FRAME4;
        }
        else if (currentShownFrame == RUN_FRAME4) {
            SDL_RenderCopy(renderer, info.animaion.run.frame5, NULL, &info.rect);
            currentShownFrame = WALK_FRAME5;
        }
        else if (currentShownFrame == RUN_FRAME5) {
            SDL_RenderCopy(renderer, info.animaion.run.frame1, NULL, &info.rect);
            currentShownFrame = WALK_FRAME1;
        }
        /* Red Card */
        else if (currentShownFrame == CARD_RED_FRAME1) {
            SDL_RenderCopy(renderer, info.animaion.card.red.frame2, NULL, &info.rect);
            currentShownFrame = CARD_RED_FRAME2;
        }
        else if (currentShownFrame == CARD_RED_FRAME2) {
            SDL_RenderCopy(renderer, info.animaion.card.red.frame3, NULL, &info.rect);
            currentShownFrame = CARD_RED_FRAME3;
        }
        else if (currentShownFrame == CARD_RED_FRAME3) {
            SDL_RenderCopy(renderer, info.animaion.card.red.frame4, NULL, &info.rect);
            currentShownFrame = CARD_RED_FRAME4;
        }
        else if (currentShownFrame == CARD_RED_FRAME4) {
            SDL_RenderCopy(renderer, info.animaion.card.red.frame5, NULL, &info.rect);
            currentShownFrame = CARD_RED_FRAME5;
        }
        else if (currentShownFrame == CARD_RED_FRAME5) {
            SDL_RenderCopy(renderer, info.animaion.card.red.frame6, NULL, &info.rect);
            currentShownFrame = CARD_RED_FRAME6;
        }
        else if (currentShownFrame == CARD_RED_FRAME6) {
            SDL_RenderCopy(renderer, info.animaion.card.red.frame1, NULL, &info.rect);
            currentShownFrame = CARD_RED_FRAME1;
        }
        /* Yellow Card */
        else if (currentShownFrame == CARD_YELLOW_FRAME1) {
            SDL_RenderCopy(renderer, info.animaion.card.yellow.frame2, NULL, &info.rect);
            currentShownFrame = CARD_YELLOW_FRAME2;
        }
        else if (currentShownFrame == CARD_YELLOW_FRAME2) {
            SDL_RenderCopy(renderer, info.animaion.card.yellow.frame3, NULL, &info.rect);
            currentShownFrame = CARD_YELLOW_FRAME3;
        }
        else if (currentShownFrame == CARD_YELLOW_FRAME3) {
            SDL_RenderCopy(renderer, info.animaion.card.yellow.frame4, NULL, &info.rect);
            currentShownFrame = CARD_YELLOW_FRAME4;
        }
        else if (currentShownFrame == CARD_YELLOW_FRAME4) {
            SDL_RenderCopy(renderer, info.animaion.card.yellow.frame5, NULL, &info.rect);
            currentShownFrame = CARD_YELLOW_FRAME5;
        }
        else if (currentShownFrame == CARD_YELLOW_FRAME5) {
            SDL_RenderCopy(renderer, info.animaion.card.yellow.frame6, NULL, &info.rect);
            currentShownFrame = CARD_YELLOW_FRAME6;
        }
        else if (currentShownFrame == CARD_YELLOW_FRAME6) {
            SDL_RenderCopy(renderer, info.animaion.card.yellow.frame1, NULL, &info.rect);
            currentShownFrame = CARD_YELLOW_FRAME1;
        }
        /* White Card */
        if (currentShownFrame == CARD_WHITE_FRAME1) {
            SDL_RenderCopy(renderer, info.animaion.card.white.frame2, NULL, &info.rect);
            currentShownFrame = CARD_WHITE_FRAME2;
        }
        else if (currentShownFrame == CARD_WHITE_FRAME2) {
            SDL_RenderCopy(renderer, info.animaion.card.white.frame3, NULL, &info.rect);
            currentShownFrame = CARD_WHITE_FRAME3;
        }
        else if (currentShownFrame == CARD_WHITE_FRAME3) {
            SDL_RenderCopy(renderer, info.animaion.card.white.frame4, NULL, &info.rect);
            currentShownFrame = CARD_WHITE_FRAME4;
        }
        else if (currentShownFrame == CARD_WHITE_FRAME4) {
            SDL_RenderCopy(renderer, info.animaion.card.white.frame5, NULL, &info.rect);
            currentShownFrame = CARD_WHITE_FRAME5;
        }
        else if (currentShownFrame == CARD_WHITE_FRAME5) {
            SDL_RenderCopy(renderer, info.animaion.card.white.frame6, NULL, &info.rect);
            currentShownFrame = CARD_WHITE_FRAME6;
        }
        else if (currentShownFrame == CARD_WHITE_FRAME6) {
            SDL_RenderCopy(renderer, info.animaion.card.white.frame1, NULL, &info.rect);
            currentShownFrame = CARD_WHITE_FRAME1;
        }
        /* Blue Card */
        else if (currentShownFrame == CARD_BLUE_FRAME1) {
            SDL_RenderCopy(renderer, info.animaion.card.blue.frame2, NULL, &info.rect);
            currentShownFrame = CARD_BLUE_FRAME2;
        }
        else if (currentShownFrame == CARD_BLUE_FRAME2) {
            SDL_RenderCopy(renderer, info.animaion.card.blue.frame3, NULL, &info.rect);
            currentShownFrame = CARD_BLUE_FRAME3;
        }
        else if (currentShownFrame == CARD_BLUE_FRAME3) {
            SDL_RenderCopy(renderer, info.animaion.card.blue.frame4, NULL, &info.rect);
            currentShownFrame = CARD_BLUE_FRAME4;
        }
        else if (currentShownFrame == CARD_BLUE_FRAME4) {
            SDL_RenderCopy(renderer, info.animaion.card.blue.frame5, NULL, &info.rect);
            currentShownFrame = CARD_BLUE_FRAME5;
        }
        else if (currentShownFrame == CARD_BLUE_FRAME5) {
            SDL_RenderCopy(renderer, info.animaion.card.blue.frame6, NULL, &info.rect);
            currentShownFrame = CARD_BLUE_FRAME6;
        }
        else if (currentShownFrame == CARD_BLUE_FRAME6) {
            SDL_RenderCopy(renderer, info.animaion.card.blue.frame1, NULL, &info.rect);
            currentShownFrame = CARD_BLUE_FRAME1;
        }
        else {
            if (debugMode)
                error("Error! (Tried to show next frame)\n");
        }
    }
    
    /*
     Resize
     */
    
    void resizeForFrame(animationType type) {
        int imgW, imgH;
        if (type == NONE) {
            warrning("Warrning AnimaionType was set to NONE (void loadAnimaion)");
            imgH = 0;
            imgW = 0;
        }
        else if (type == NORMAL) {
            SDL_QueryTexture(info.Texture, NULL, NULL, &imgW, &imgH);
        }
        // Walking Frames
        else if (type == WALK_FRAME1) {
            SDL_QueryTexture(info.animaion.walk.frame1, NULL, NULL, &imgW, &imgH);
        }
        else if (type == WALK_FRAME2) {
            SDL_QueryTexture(info.animaion.walk.frame2, NULL, NULL, &imgW, &imgH);
        }
        else if (type == WALK_FRAME3) {
            SDL_QueryTexture(info.animaion.walk.frame3, NULL, NULL, &imgW, &imgH);
        }
        else if (type == WALK_FRAME4) {
            SDL_QueryTexture(info.animaion.walk.frame4, NULL, NULL, &imgW, &imgH);
        }
        else if (type == WALK_FRAME5) {
            SDL_QueryTexture(info.animaion.walk.frame5, NULL, NULL, &imgW, &imgH);
        }
        // Runing Frames
        else if (type == RUN_FRAME1) {
            SDL_QueryTexture(info.animaion.run.frame1, NULL, NULL, &imgW, &imgH);
        }
        else if (type == RUN_FRAME2) {
            SDL_QueryTexture(info.animaion.run.frame2, NULL, NULL, &imgW, &imgH);
        }
        else if (type == RUN_FRAME3) {
            SDL_QueryTexture(info.animaion.run.frame3, NULL, NULL, &imgW, &imgH);
        }
        else if (type == RUN_FRAME4) {
            SDL_QueryTexture(info.animaion.run.frame4, NULL, NULL, &imgW, &imgH);
        }
        else if (type == RUN_FRAME5) {
            SDL_QueryTexture(info.animaion.run.frame5, NULL, NULL, &imgW, &imgH);
        }
        // Card Frames
        // Red Card
        else if (type == CARD_RED_FRAME1) {
            SDL_QueryTexture(info.animaion.card.red.frame1, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_RED_FRAME2) {
            SDL_QueryTexture(info.animaion.card.red.frame2, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_RED_FRAME3) {
            SDL_QueryTexture(info.animaion.card.red.frame3, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_RED_FRAME4) {
            SDL_QueryTexture(info.animaion.card.red.frame4, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_RED_FRAME5) {
            SDL_QueryTexture(info.animaion.card.red.frame5, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_RED_FRAME6) {
            SDL_QueryTexture(info.animaion.card.red.frame6, NULL, NULL, &imgW, &imgH);
        }
            // Yellow Card
        else if (type == CARD_YELLOW_FRAME1) {
            SDL_QueryTexture(info.animaion.card.yellow.frame1, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_YELLOW_FRAME2) {
            SDL_QueryTexture(info.animaion.card.yellow.frame2, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_YELLOW_FRAME3) {
            SDL_QueryTexture(info.animaion.card.yellow.frame3, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_YELLOW_FRAME4) {
            SDL_QueryTexture(info.animaion.card.yellow.frame4, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_YELLOW_FRAME5) {
            SDL_QueryTexture(info.animaion.card.yellow.frame5, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_YELLOW_FRAME6) {
            SDL_QueryTexture(info.animaion.card.yellow.frame6, NULL, NULL, &imgW, &imgH);
        }
            // White Card
        else if (type == CARD_WHITE_FRAME1) {
            SDL_QueryTexture(info.animaion.card.white.frame1, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_WHITE_FRAME2) {
            SDL_QueryTexture(info.animaion.card.white.frame2, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_WHITE_FRAME3) {
            SDL_QueryTexture(info.animaion.card.white.frame3, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_WHITE_FRAME4) {
            SDL_QueryTexture(info.animaion.card.white.frame4, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_WHITE_FRAME5) {
            SDL_QueryTexture(info.animaion.card.white.frame5, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_WHITE_FRAME6) {
            SDL_QueryTexture(info.animaion.card.white.frame6, NULL, NULL, &imgW, &imgH);
        }
            // Blue Card
        else if (type == CARD_BLUE_FRAME1) {
            SDL_QueryTexture(info.animaion.card.blue.frame1, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_BLUE_FRAME2) {
            SDL_QueryTexture(info.animaion.card.blue.frame2, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_BLUE_FRAME3) {
            SDL_QueryTexture(info.animaion.card.blue.frame3, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_BLUE_FRAME4) {
            SDL_QueryTexture(info.animaion.card.blue.frame4, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_BLUE_FRAME5) {
            SDL_QueryTexture(info.animaion.card.blue.frame5, NULL, NULL, &imgW, &imgH);
        }
        else if (type == CARD_BLUE_FRAME6) {
            SDL_QueryTexture(info.animaion.card.blue.frame6, NULL, NULL, &imgW, &imgH);
        }
        else {
            error("Not a valid type! (Tried to resize frame)\n");
            imgH = 0;
            imgW = 0;
        }
        info.rect.h = imgH * pixelsPerGamePixels;
        info.rect.w = imgW * pixelsPerGamePixels;
    }
    
    void goTo(int x, int y) {
        importantInfo("Function activated! goTo(moveType type)\n");
        worldX = x;
        worldY = y;
        info.rect.x = x * pixelsPerGamePixels;
        info.rect.y = y * pixelsPerGamePixels;
    }
    
    void alphaGoTo(int x, int y) {
        importantInfo("Function activated! alphaGoTo(int x, int y)\n");
        worldX = x;
        worldY = y;
        info.rect.x = round((worldX * pixelsPerGamePixels * camrea.zoom) - camrea.x);
        info.rect.y = round((worldY * pixelsPerGamePixels * camrea.zoom) - camrea.y);
    }
    
    void move(moveType type) {
        importantInfo("Function activated! move(moveType type)\n");
        if (type == UP) {
            goTo(worldX, worldY - 1);
        }
        else if (type == DOWN) {
            goTo(worldX, worldY + 1);
        }
        else if (type == LEFT) {
            goTo(worldX - 1, worldY);
        }
        else if (type == RIGHT) {
            goTo(worldX + 1, worldY);
        }
    }
    
    void alphaMove(moveType type) {
        importantInfo("Function activated! alphaMove(moveType type)\n");
        if (type == UP) {
            importantInfo("UP Detected!\n");
            alphaGoTo(worldX, worldY - 1);
        }
        else if (type == DOWN) {
            importantInfo("DOWN Detected!\n");
            alphaGoTo(worldX, worldY + 1);
        }
        else if (type == LEFT) {
            importantInfo("LEFT Detected!\n");
            alphaGoTo(worldX - 1, worldY);
        }
        else if (type == RIGHT) {
            importantInfo("RIGHT Detected!\n");
            alphaGoTo(worldX + 1, worldY);
        }
    }
    
    void updateWidthHeight() {
        // Rebuild rect from world position so zoom changes don't drift position.
        animationType typeToResize = currentShownFrame == NONE ? NORMAL : currentShownFrame;
        resizeForFrame(typeToResize);
        info.rect.h = camrea.zoom * info.rect.h;
        info.rect.w = camrea.zoom * info.rect.w;
        info.rect.x = round((worldX * pixelsPerGamePixels * camrea.zoom) - camrea.x);
        info.rect.y = round((worldY * pixelsPerGamePixels * camrea.zoom) - camrea.y);
    }
};

class field {
public:
    fieldSprite info;
    fieldType currentFieldType = FIELD_NONE;
    string spriteName;
    int worldX = 0;
    int worldY = 0;
    
    field(string importedSpriteName) {
        spriteName = importedSpriteName;
        initTextures();
    }
    
    void init(string importedSpriteName) {
        spriteName = importedSpriteName;
        initTextures();
        goTo(0, 0);
    }
    
    void initTextures() {
        info.textures.normal.normal = nullptr;
        info.textures.normal.snow = nullptr;
        info.textures.normal.rain = nullptr;
        info.textures.debug.normal = nullptr;
        info.textures.debug.snow = nullptr;
        info.textures.debug.rain = nullptr;
    }
    
    void goTo(int x, int y) {
        worldX = x;
        worldY = y;
        info.rect.x = x * pixelsPerGamePixels;
        info.rect.y = y * pixelsPerGamePixels;
    }
    
    void load(string pathToFile, fieldType type) {
        if (type == DEBUG_FIELD) {
            printInfo("Loading Texture...\n");
            info.textures.debug.normal = IMG_LoadTexture(renderer, pathToFile.c_str());
            if (!info.textures.debug.normal) {
                warrning("FIELD LOAD ERROR: " + (string)IMG_GetError() + "\n");
            }
        }
    }
    
    ~field() {
        if (info.textures.debug.normal) SDL_DestroyTexture(info.textures.debug.normal);
        if (info.textures.normal.normal) SDL_DestroyTexture(info.textures.normal.normal);
        if (info.textures.normal.snow) SDL_DestroyTexture(info.textures.normal.snow);
        if (info.textures.normal.rain) SDL_DestroyTexture(info.textures.normal.rain);
        if (info.textures.debug.snow) SDL_DestroyTexture(info.textures.debug.snow);
        if (info.textures.debug.rain) SDL_DestroyTexture(info.textures.debug.rain);
    }
    
    void alphaDisplay(fieldType type) {
        currentFieldType = type;
        if (type == DEBUG_FIELD) {
            SDL_RenderCopy(renderer, info.textures.debug.normal, NULL, &info.rect);
        }
    }
    
    void display(fieldType type) {
        currentFieldType = type;
        resizeForFrame(type);
        if (type == DEBUG_FIELD) {
            SDL_RenderCopy(renderer, info.textures.debug.normal, NULL, &info.rect);
        }
    }
    
    void resizeForFrame(fieldType type) {
        int imgW, imgH;
        if (type == DEBUG_FIELD) {
            SDL_QueryTexture(info.textures.debug.normal, NULL, NULL, &imgW, &imgH);
        }
        else {
            error("Error Not a vaid type! resizeForFrame(fieldType type)\n");
            imgH = 0;
            imgW = 0;
        }
        info.rect.h = imgH * pixelsPerGamePixels;
        info.rect.w = imgW * pixelsPerGamePixels;
    }
    
    void alphaMove(moveType type) {
        importantInfo("Function activated! alphaMove(moveType type)\n");
        if (type == UP) {
            importantInfo("UP Detected!\n");
            alphaGoTo(worldX, worldY - 1);
        }
        else if (type == DOWN) {
            importantInfo("DOWN Detected!\n");
            alphaGoTo(worldX, worldY + 1);
        }
        else if (type == LEFT) {
            importantInfo("LEFT Detected!\n");
            alphaGoTo(worldX - 1, worldY);
        }
        else if (type == RIGHT) {
            importantInfo("RIGHT Detected!\n");
            alphaGoTo(worldX + 1, worldY);
        }
    }
    
    void alphaGoTo(int x, int y) {
        importantInfo("Function activated! alphaGoTo(int x, int y)\n");
        worldX = x;
        worldY = y;
        info.rect.x = ((worldX * pixelsPerGamePixels * camrea.zoom) - camrea.x);
        info.rect.y = ((worldY * pixelsPerGamePixels * camrea.zoom) - camrea.y);
    }
    
    void updateWidthHeight() {
        fieldType typeToResize = currentFieldType == FIELD_NONE ? DEBUG_FIELD : currentFieldType;
        resizeForFrame(typeToResize);
        info.rect.h = camrea.zoom * info.rect.h;
        info.rect.w = camrea.zoom * info.rect.w;
        info.rect.x = ((worldX * pixelsPerGamePixels * camrea.zoom) - camrea.x);
        info.rect.y = ((worldY * pixelsPerGamePixels * camrea.zoom) - camrea.y);
    }
};

class ball {
public:
    ballType currentShownFrame = NONE_BALL;
    string spriteName;
    double worldX = 0;
    double worldY = 0;
    double mometeum = 0;
    int targetX = 0;
    int targetY = 0;
    ballSprite info;
    int &currentX = info.rect.x;
    int &currentY = info.rect.y;
    
    void setFacingDirection(int x, int y) {
        targetX = x;
        targetY = y;
    }
    
    void updateLocation() {
        if (targetX >= currentX && targetY >= currentY) {
            worldX += mometeum;
            worldY += mometeum;
        }
        else if (targetX <= currentX && targetY >= currentY) {
            worldX -= mometeum;
            worldY += mometeum;
        }
        else if (targetX <= currentX && targetY <= currentY) {
            worldX -= mometeum;
            worldY -= mometeum;
        }
        else if (targetX >= currentX && targetY <= currentY) {
            worldX += mometeum;
            worldY -= mometeum;
        }
        else {
            return;
        }
    }
    
    ball(string importedSpriteName) {
        spriteName = importedSpriteName;
        initTexture();
        goTo(0, 0);
        info.rect.x = 0;
        info.rect.y = 0;
        info.rect.h = 0;
        info.rect.w = 0;
    }
    
    void initTexture() {
        info.texture = nullptr;
    }
    
    void goTo(int x, int y) {
        worldX = x;
        worldY = y;
        info.rect.x = x * pixelsPerGamePixels;
        info.rect.y = y * pixelsPerGamePixels;
    }
    
    void load(string pathToFile, ballType type) {
        if (type == DEBUG_BALL) {
            printInfo("Loading Texture...\n");
            info.texture = IMG_LoadTexture(renderer, pathToFile.c_str());
            if (!info.texture) {
                warrning("FIELD LOAD ERROR: " + (string)IMG_GetError() + "\n");
            }
        }
    }
    
    ~ball() {
        if (info.texture) SDL_DestroyTexture(info.texture);
    }
    
    void alphaDisplay(ballType type) {
        currentShownFrame = type;
        if (type == DEBUG_BALL) {
            SDL_RenderCopy(renderer, info.texture, NULL, &info.rect);
        }
    }
    
    void display(ballType type) {
        currentShownFrame = type;
        resizeForFrame(type);
        if (type == DEBUG_BALL) {
            SDL_RenderCopy(renderer, info.texture, NULL, &info.rect);
        }
    }
    
    void resizeForFrame(ballType type) {
        int imgW, imgH;
        if (type == DEBUG_BALL) {
            SDL_QueryTexture(info.texture, NULL, NULL, &imgW, &imgH);
        }
        else {
            error("Error Not a vaid type! resizeForFrame(fieldType type)\n");
            imgH = 0;
            imgW = 0;
        }
        info.rect.h = imgH * pixelsPerGamePixels;
        info.rect.w = imgW * pixelsPerGamePixels;
    }
    
    void alphaMove(moveType type) {
        importantInfo("Function activated! alphaMove(moveType type)\n");
        if (type == UP) {
            importantInfo("UP Detected!\n");
            alphaGoTo(worldX, worldY - 1);
        }
        else if (type == DOWN) {
            importantInfo("DOWN Detected!\n");
            alphaGoTo(worldX, worldY + 1);
        }
        else if (type == LEFT) {
            importantInfo("LEFT Detected!\n");
            alphaGoTo(worldX - 1, worldY);
        }
        else if (type == RIGHT) {
            importantInfo("RIGHT Detected!\n");
            alphaGoTo(worldX + 1, worldY);
        }
    }
    
    void alphaGoTo(int x, int y) {
        importantInfo("Function activated! alphaGoTo(int x, int y)\n");
        worldX = x;
        worldY = y;
        info.rect.x = ((worldX * pixelsPerGamePixels * camrea.zoom) - camrea.x);
        info.rect.y = ((worldY * pixelsPerGamePixels * camrea.zoom) - camrea.y);
    }
    
    void updateWidthHeight() {
        ballType typeToResize = currentShownFrame == NONE_BALL ? DEBUG_BALL : currentShownFrame;
        resizeForFrame(typeToResize);
        info.rect.h = camrea.zoom * info.rect.h;
        info.rect.w = camrea.zoom * info.rect.w;
        info.rect.x = ((worldX * pixelsPerGamePixels * camrea.zoom) - camrea.x);
        info.rect.y = ((worldY * pixelsPerGamePixels * camrea.zoom) - camrea.y);
    }
};

/*-----------------------------------------------------------------
  -----------------------------int Main----------------------------
  -----------------------------------------------------------------*/

int main() {
    debugMode = true;
    loopNumber = 0;
    updateRenderingOnResize = false;
    muted = true;
    
    init();
    
    /*
     Load sprites:
     */
    
    ball debugBall("debugBall");
    debugBall.load("/Users/yec/Documents/Retro Cup/Retro Cup/.assets/ball/debugBall.png", DEBUG_BALL);
    debugBall.mometeum = 1;
    
    field debugField("debugSprite");
    debugField.load("/Users/yec/Documents/Retro Cup/Retro Cup/.assets/field/debugField.png", DEBUG_FIELD);
    
    human debugPlayer("debugPlayer");
    debugPlayer.loadAnimation(vector<string> {"/Users/yec/Documents/Retro Cup/Retro Cup/.assets/players/debugPlayer.png"}, NORMAL);
    
    human debugPlayerAI("debugPlayerAI");
    debugPlayerAI.loadAnimation(vector<string> {"/Users/yec/Documents/Retro Cup/Retro Cup/.assets/players/debugPlayer.png"}, NORMAL);
    
    debugPlayer.alphaGoTo(0, 0);
    debugField.alphaGoTo(0, 0);
    
    bool WindowShouldClose = false;
    SDL_Event event;
    bool IsPrintLoop = false;
    int mouseX = 0;
    int mouseY = 0;
    
    Key keyPressed = GAME_KEY_NONE;
    
    /*
     |----------------|
     |Entering loop...|
     |________________|
     */
    printBold("Entering Loop...\n");
    while (!WindowShouldClose) {
        loopNumber ++;
        updateFPS();
        
        if (debugMode)
            IsPrintLoop = isCommonMultiple(loopNumber,120);
        /* Only shows every 120 loops */
        if (IsPrintLoop) {
            cout <<
            "\n\n---------------------------------------------------------------\n" <<
            "---------------Loop #" << loopNumber << "---------------------\n" <<
            "---------------------------------------------------------------\n";
            printInfo(toString(currentFPS) + "\n");
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) WindowShouldClose = true;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        keyPressed = GAME_KEY_W;
                        break;
                    case SDLK_UP:
                        keyPressed = GAME_KEY_UP;
                        break;
                    case SDLK_s:
                        keyPressed = GAME_KEY_S;
                        break;
                    case SDLK_DOWN:
                        keyPressed = GAME_KEY_DOWN;
                        break;
                    case SDLK_a:
                        keyPressed = GAME_KEY_A;
                        break;
                    case SDLK_LEFT:
                        keyPressed = GAME_KEY_LEFT;
                        break;
                    case SDLK_d:
                        keyPressed = GAME_KEY_D;
                        break;
                    case SDLK_RIGHT:
                        keyPressed = GAME_KEY_RIGHT;
                        break;
                    case SDLK_SPACE:
                        printInfo("Spacebar pressed\n");
                        keyPressed = GAME_KEY_SPACE;
                        break;
                }
            }
            if (event.type == SDL_WINDOWEVENT) {
                // Check the specific window event
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        printInfo("Window resized to: " + std::to_string(event.window.data1) + "x" + std::to_string(event.window.data2) + "\n");
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        warrning("Mouse entered window\n");
                        break;
                    case SDL_WINDOWEVENT_LEAVE:
                        warrning("Mouse left window\n");
                        break;
                    case SDL_WINDOWEVENT_MINIMIZED:
                        warrning("Window minamized\n");
                        break;
                    case SDL_APP_DIDENTERFOREGROUND:
                        SDL_RestoreWindow(window);
                        SDL_RaiseWindow(window);
                        break;
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        warrning("Window foucsed\n");
                        break;
                    case SDL_WINDOWEVENT_FOCUS_LOST:
                        warrning("Window unfoucused\n");
                        break;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                /* Track mouse position */
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (debugMode)
                        printInfo("Clicked at: " + toString(mouseX) + ", " + toString(mouseY) + "\n");
                    debugBall.setFacingDirection(mouseX, mouseY);
                }
            }
        }
        if (isCommonMultiple(loopNumber,120)) {
            printInfo("Mouse position: " + toString(mouseX) + ", " + toString(mouseY) + "\n");
        }
        /*
         ALPHA TESTING STUFF
         */
        if (keyPressed == GAME_KEY_W) {
            //camrea.y += pixelsPerGamePixels;
            debugPlayer.alphaMove(UP);
        }
        else if (keyPressed == GAME_KEY_A || keyPressed == GAME_KEY_LEFT) {
            //camrea.x += pixelsPerGamePixels;
            debugPlayer.alphaMove(LEFT);
        }
        else if (keyPressed == GAME_KEY_S) {
            //camrea.y -= pixelsPerGamePixels;
            debugPlayer.alphaMove(DOWN);
        }
        else if (keyPressed == GAME_KEY_D || keyPressed == GAME_KEY_RIGHT) {
            //camrea.x -= pixelsPerGamePixels;
            debugPlayer.alphaMove(RIGHT);
        }
        else if (keyPressed == GAME_KEY_UP) {
            camrea.zoomIn(0.2);
        }
        else if (keyPressed == GAME_KEY_DOWN) {
            camrea.zoomOut(0.2);
        }
        //camrea.zoomIn(0.01);
        
        debugPlayer.resizeForFrame(NORMAL);
        debugField.resizeForFrame(DEBUG_FIELD);
        debugBall.resizeForFrame(DEBUG_BALL);
        
        
        debugField.updateWidthHeight();
        debugPlayer.updateWidthHeight();
        debugBall.updateWidthHeight();
        
        debugBall.updateLocation();
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /* Make the opacity max */
        SDL_RenderClear(renderer); /* Clear the screen  */
        
        /* Rendering Each Sprite: */
        debugField.alphaDisplay(DEBUG_FIELD);
        debugPlayer.alphaDisplay(NORMAL);
        debugBall.alphaDisplay(DEBUG_BALL);
        
        SDL_RenderPresent(renderer);
        
        /*
         Reset the stuff
         */
        keyPressed = GAME_KEY_NONE;
    }
    printBold("\nExited loop\n");
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    /*
     Saving data:
     */
    
    /*
     std::ofstream saveFile(getSaveFilePath(), std::ios::out | std::ios::binary);
     if (!saveFile.is_open()) {
     error("Error opening file!\n");
     return 1;
     }
     
     writeIntToFile(saveFile, 12);
     */
    
    double largestFPS = largestFPSlist[0];
    for (double num : largestFPSlist) {
        if (num > largestFPS) {
            largestFPS = num;
        }
    }
    
    double lowestFPS = largestFPSlist[0];
    for (double num : largestFPSlist) {
        if (num < lowestFPS) {
            lowestFPS = num;
        }
    }
    
    int lengthOfList = (int)largestFPSlist.size();
    double addedUpNumber = 0;
    for (double num : largestFPSlist) {
        addedUpNumber += num;
    }
    double averageFPS = addedUpNumber/lengthOfList;
    
    printBold( (string)"\n\n\n--------------------------------------------------" + "\n" +
          "-----------------Ending information---------------" + "\n" +
          "--------------------------------------------------" + "\n");
    printEndInfo("Highest FPS:         ", largestFPS);
    printEndInfo("Lowest FPS:          ", lowestFPS);
    printEndInfo("Average FPS:         ", averageFPS);
    printEndInfo("Ending Camrea state: ", ("{" + std::to_string(camrea.zoom) + "," + std::to_string(camrea.x) + "," + std::to_string(camrea.y) + "}"));
    // -------------------------
    // -------------------------
    // --------------------------------------------------
    printBold("\n                  Window State:\n");
    printEndInfo("Screen Size: ", ("{" + std::to_string(screenSize.width) + "," + std::to_string(screenSize.height) + "}\n"));
    printBold("\n                  Sprite States:\n");
    printEndInfo("debugPlayer State:          ", ("{" + std::to_string(debugPlayer.info.rect.x) + "," + std::to_string(debugPlayer.info.rect.y) + "," + std::to_string(debugPlayer.info.rect.h) + "," + std::to_string(debugPlayer.info.rect.w) + "}"));
    printEndInfo("debugField State:           ", ("{" + std::to_string(debugField.info.rect.x) + "," + std::to_string(debugField.info.rect.y) + "," + std::to_string(debugField.info.rect.h) + "," + std::to_string(debugField.info.rect.w) + "}"));
    printEndInfo("debugBall State:            ", ("{" + std::to_string(debugBall.info.rect.x) + "," + std::to_string(debugBall.info.rect.y) + "," + std::to_string(debugBall.info.rect.h) + "," + std::to_string(debugBall.info.rect.w) + "}"));
    printEndInfo("debugBall Facing Direction: ", ("{" + std::to_string(debugBall.targetX) + "," + std::to_string(debugBall.targetY) + "}\n"));
    
    warrning("\nENDING PROGRAM...\n\n\n\n");
    
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
