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
 For more about OpenGL go to OpenGl.com
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
        Sprite stands for a thing on the screen like the the field, the player, or the ref.
    }
    info {
        We are using SDL2 for displaying and we are still deciding what to use for sound.
        All comments are with muitiline comments.
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

#include "Color Text.hpp"

/* Are using these: */
using
std::cout,
std::cin,
std::string,
std::endl,
std::vector;

/*-----------------------------------------------------------------
  --------------------------------Enums----------------------------
  -----------------------------------------------------------------*/

typedef enum {
    // Letters:
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    
    // Numbers:
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    
    // Arrows:
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT
} Key;

typedef enum {
    /* Normal */
    NORMAL,
    
    /* Walk */
    WALK,
    WALK_FRAME1,
    WALK_FRAME2,
    WALK_FRAME3,
    WALK_FRAME4,
    WALK_FRAME5,
    
    /* Run */
    RUN,
    RUN_FRAME1,
    RUN_FRAME2,
    RUN_FRAME3,
    RUN_FRAME4,
    RUN_FRAME5,
    
    /*
     Cards:
     */
    CARD,
    CARDS,
    
    /* Red */
    CARD_RED,
    CARD_RED_FRAME1,
    CARD_RED_FRAME2,
    CARD_RED_FRAME3,
    CARD_RED_FRAME4,
    CARD_RED_FRAME5,
    CARD_RED_FRAME6,
    
    /* Yellow */
    CARD_YELLOW,
    CARD_YELLOW_FRAME1,
    CARD_YELLOW_FRAME2,
    CARD_YELLOW_FRAME3,
    CARD_YELLOW_FRAME4,
    CARD_YELLOW_FRAME5,
    CARD_YELLOW_FRAME6,
    
    /* White */
    CARD_WHITE,
    CARD_WHITE_FRAME1,
    CARD_WHITE_FRAME2,
    CARD_WHITE_FRAME3,
    CARD_WHITE_FRAME4,
    CARD_WHITE_FRAME5,
    CARD_WHITE_FRAME6,
    
    /* Blue */
    CARD_BLUE,
    CARD_BLUE_FRAME1,
    CARD_BLUE_FRAME2,
    CARD_BLUE_FRAME3,
    CARD_BLUE_FRAME4,
    CARD_BLUE_FRAME5,
    CARD_BLUE_FRAME6,
    
    /* Other */
    NONE,
    ALL
} animationType;

typedef enum {
    FIELD_NONE,
    
    DEBUG_FIELD,
    DEBUG_FIELD_SNOW,
    DEBUG_FIELD_RAIN,
    
    NORMAL_FIELD,
    NORMAL_FIELD_SNOW,
    NORMAL_FIELD_RAIN,
} fieldType;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    JUMP,
} moveType;

/*-----------------------------------------------------------------
  ------------------------------Structs----------------------------
  -----------------------------------------------------------------*/

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

/*-----------------------------------------------------------------
  -------------------------Global Varriables-----------------------
  -----------------------------------------------------------------*/

SDL_Renderer* renderer;
SDL_Window* window;
int pixelsPerGamePixels;
bool debugMode = true;
float zoom;

/*-----------------------------------------------------------------
  -----------------------------Functions---------------------------
  -----------------------------------------------------------------*/

void error(string errorMessage) {
    if (debugMode)
        cout << (startText+startBoldText+redText+endText) << errorMessage << resetText;
}

int RandomInt(int low, int high) {
    /* 1. Obtain a random seed from the hardware or OS
          (intended to be non-deterministic when possible) */
    std::random_device rd;
    
    /* 2. Initialize a high-quality pseudo-random number engine with the seed
          The Mersenne Twister engine (mt19937) is a common choice */
    std::mt19937 gen(rd());
    
    /* 3. Define the desired range (e.g., between 1 and 100 inclusive)
          uniform_int_distribution ensures uniform distribution across the range */
    std::uniform_int_distribution<> distrib(low, high);
    
    /* 4. Generate and return the random number */
    int randomNumber = distrib(gen);
    
    return randomNumber;
}

void pauseMicroseconds(int microseconds) {
    std::this_thread::sleep_for(std::chrono::microseconds(microseconds));
}

void pauseMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void pauseSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void pauseMinutes(int minutes) {
    std::this_thread::sleep_for(std::chrono::minutes(minutes));
}

void pauseHours(int hours) {
    std::this_thread::sleep_for(std::chrono::hours(hours));
}

void pauseDays(int days) {
    std::this_thread::sleep_for(std::chrono::days(days));
}

void pauseWeek(int weeks) {
    std::this_thread::sleep_for(std::chrono::weeks(weeks));
}

void pauseMonth(int months) {
    std::this_thread::sleep_for(std::chrono::months(months));
}

void pauseYear(int years) {
    std::this_thread::sleep_for(std::chrono::years(years));
}

bool isCommonMultiple(int Number, int Multiple) {
    if ((Number % Multiple) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool contains(string inputString, string contains) {
    if (inputString.find(contains) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

rectangle getScreenSize(int widthPixels) {
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0) {
        if (debugMode)
        cout << "Error, could not get screen size due to error: " << SDL_GetError() << "\n";
    }
    
    rectangle builtInScreen;
    builtInScreen.width = displayMode.w;
    builtInScreen.height = displayMode.h;
    if (debugMode)
    cout << "Built in screen: {" << builtInScreen.width << "," << builtInScreen.height << "}" << endl;
    
    /* MATH (Uggghhh...) */
    
    /* STEP ONE: */
    rectangle stepOne;
    stepOne.width = floor(builtInScreen.width/widthPixels);
    stepOne.gameWidth = widthPixels;
    
    /* STEP TWO: */
    rectangle stepTwo;
    stepTwo.width = stepOne.width * widthPixels;
    while (stepTwo.width < builtInScreen.width) {
        stepOne.gameWidth += 1;
        stepTwo.width += stepOne.width;
        if (stepTwo.width > builtInScreen.width) {
            stepTwo.width -= stepOne.width;
            stepOne.gameWidth -= 1;
        }
    }
    
    /* STEP THREE: */
    rectangle stepThree;
    stepThree.width = stepTwo.width;
        /* Calcuate the height. */
    stepThree.height = floor(builtInScreen.height/stepOne.width) * stepOne.width;
    stepOne.gameHeight = floor(builtInScreen.height/stepOne.width);
    
    /* Operating system (Need to take away menu bar amount if mac) */
#if defined(__APPLE__)
    if (stepOne.width == 1) {
        stepThree.height -= 74;
        stepOne.gameHeight -= 74;
    }
    else if (stepOne.width == 2) {
        stepThree.height -= 76;
        stepOne.gameHeight -= 38;
    }
    else if (stepOne.width == 3) {
        stepThree.height -= 75;
        stepOne.gameHeight -= 25;
    }
    else if (stepOne.width == 4) {
        stepThree.height -= 72;
        stepOne.gameHeight -= 18;
    }
    else if (stepOne.width == 5) {
        stepThree.height -= 75;
        stepOne.gameHeight -= 15;
    }
    else if (stepOne.width == 6) {
        stepThree.height -= 72;
        stepOne.gameHeight -= 12;
    }
    else if (stepOne.width == 7) {
        stepThree.height -= 77;
        stepOne.gameHeight -= 11;
    }
    else if (stepOne.width == 8) {
        stepThree.height -= 72;
        stepOne.gameHeight -= 9;
    }
    else if (stepOne.width == 9) {
        stepThree.height -= 72;
        stepOne.gameHeight -= 8;
    }
    else if (stepOne.width == 10) {
        stepThree.height -= 70;
        stepOne.gameHeight -= 7;
    }
#endif
    
    // Return the value:
    rectangle returnRectange = stepThree;
    returnRectange.originalHeight = builtInScreen.height;
    returnRectange.originalWidth = builtInScreen.width;
    returnRectange.pixels = stepOne.width;
    returnRectange.gameHeight = stepOne.gameHeight;
    returnRectange.gameWidth = stepOne.gameWidth;
    return returnRectange;
}

void print(string str) {
    if (debugMode) {
        cout << str;
    }
}

/*-----------------------------------------------------------------
  -----------------------------Classes-----------------------------
  -----------------------------------------------------------------*/

class human {
public:
    humanInfo info;
    animationType currentShownFrame = NONE;
    string spriteName;
    
    void init(string importedSpriteName) {
        spriteName = importedSpriteName;
        goTo(0, 1);
    }
    
    /*
     ------------------------------------------------------------------------------------------
     --------------------------------Loading animations----------------------------------------
     ------------------------------------------------------------------------------------------
     */
    
    void loadAnimation(vector<string> filePaths, animationType AnimationType) {
        if (AnimationType == NORMAL) {
            string currentFilePath = filePaths[0];
            info.Texture = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.normalTextureIsLoaded = true;
        }
        else if (AnimationType == RUN) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.run.frame1 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.run.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.run.frame2 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.run.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.run.frame3 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.run.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.run.frame4 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.run.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.run.frame5 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.run.frame5IsLoaded = true;
            
            info.animaion.runIsLoaded = true;
            
            if (info.animaion.walkIsLoaded && info.animaion.cardsAreLoaded) {
                info.allAnimationsAreLoaded = true;
            }
        }
        else if (AnimationType == WALK) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.walk.frame1 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.walk.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.walk.frame2 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.walk.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.walk.frame3 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.walk.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.walk.frame4 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.walk.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.walk.frame5 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.walk.frame5IsLoaded = true;
            
            info.animaion.walkIsLoaded = true;
            
            if (info.animaion.runIsLoaded && info.animaion.cardsAreLoaded) {
                info.allAnimationsAreLoaded = true;
            }
        }
        else if (AnimationType == CARD_RED) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.red.frame1 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.red.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.red.frame2 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.red.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.red.frame3 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.red.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.red.frame4 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.red.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.red.frame5 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.red.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.red.frame6 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.red.frame6IsLoaded = true;
            
            info.animaion.card.redIsLoaded = true;
            
            if (info.animaion.card.blueIsLoaded && info.animaion.card.whiteIsLoaded && info.animaion.card.yellowIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        if (AnimationType == CARD_YELLOW) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.yellow.frame1 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.yellow.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.yellow.frame2 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.yellow.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.yellow.frame3 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.yellow.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.yellow.frame4 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.yellow.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.yellow.frame5 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.yellow.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.yellow.frame6 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.yellow.frame6IsLoaded = true;
            
            info.animaion.card.yellowIsLoaded = true;
            
            if (info.animaion.card.blueIsLoaded && info.animaion.card.whiteIsLoaded && info.animaion.card.redIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        if (AnimationType == CARD_BLUE) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.blue.frame1 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.blue.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.blue.frame2 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.blue.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.blue.frame3 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.blue.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.blue.frame4 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.blue.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.blue.frame5 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.blue.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.blue.frame6 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.blue.frame6IsLoaded = true;
            
            info.animaion.card.blueIsLoaded = true;
            
            if (info.animaion.card.yellowIsLoaded && info.animaion.card.whiteIsLoaded && info.animaion.card.redIsLoaded) {
                info.animaion.cardsAreLoaded = true;
                if (info.animaion.runIsLoaded && info.animaion.walkIsLoaded) {
                    info.allAnimationsAreLoaded = true;
                }
            }
        }
        if (AnimationType == CARD_WHITE) {
            // #1
            string currentFilePath = filePaths[0];
            info.animaion.card.white.frame1 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.white.frame1IsLoaded = true;
            
            // #2
            currentFilePath = filePaths[1];
            info.animaion.card.white.frame2 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.white.frame2IsLoaded = true;
            
            // #3
            currentFilePath = filePaths[2];
            info.animaion.card.white.frame3 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.white.frame3IsLoaded = true;

            // #4
            currentFilePath = filePaths[3];
            info.animaion.card.white.frame4 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.white.frame4IsLoaded = true;

            // #5
            currentFilePath = filePaths[4];
            info.animaion.card.white.frame5 = IMG_LoadTexture(renderer, currentFilePath.c_str());
            info.animaion.card.white.frame5IsLoaded = true;
            
            // #6
            currentFilePath = filePaths[5];
            info.animaion.card.white.frame6 = IMG_LoadTexture(renderer, currentFilePath.c_str());
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
    
    void display(animationType type) {
        resizeForFrame(type);
        currentShownFrame = type;
        if (type == NORMAL) {
            SDL_RenderCopy(renderer, info.Texture, NULL, &info.rect);
            currentShownFrame = NORMAL;
        }
        // Walking Frames
        if (type == WALK_FRAME1) {
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

    void unload(animationType type) {
        if (type == NORMAL) {
            SDL_RenderCopy(renderer, info.Texture, NULL, &info.rect);
        }
        // Walking Frames
        if (type == WALK_FRAME1) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame1IsLoaded) {
                SDL_DestroyTexture(info.animaion.walk.frame1);
            }
        }
        else if (type == WALK_FRAME2) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame2IsLoaded) {
                SDL_DestroyTexture(info.animaion.walk.frame2);
            }
        }
        else if (type == WALK_FRAME3) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame3IsLoaded) {
                SDL_DestroyTexture(info.animaion.walk.frame3);
            }
        }
        else if (type == WALK_FRAME4) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame4IsLoaded) {
                SDL_DestroyTexture(info.animaion.walk.frame4);
            }
        }
        else if (type == WALK_FRAME5) {
            if (info.animaion.walkIsLoaded || info.allAnimationsAreLoaded || info.animaion.walk.frame5IsLoaded) {
                SDL_DestroyTexture(info.animaion.walk.frame5);
            }
        }
        else if (type == WALK) {
            if (info.animaion.walkIsLoaded || (info.animaion.walk.frame1IsLoaded &&
                                               info.animaion.walk.frame2IsLoaded &&
                                               info.animaion.walk.frame3IsLoaded &&
                                               info.animaion.walk.frame4IsLoaded &&
                                               info.animaion.walk.frame5IsLoaded )){
                SDL_DestroyTexture(info.animaion.walk.frame1);
                SDL_DestroyTexture(info.animaion.walk.frame2);
                SDL_DestroyTexture(info.animaion.walk.frame3);
                SDL_DestroyTexture(info.animaion.walk.frame4);
                SDL_DestroyTexture(info.animaion.walk.frame5);
            }
        }
        // Runing Frames
        else if (type == RUN_FRAME1) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame1IsLoaded) {
                SDL_DestroyTexture(info.animaion.run.frame1);
            }
        }
        else if (type == RUN_FRAME2) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame2IsLoaded) {
                SDL_DestroyTexture(info.animaion.run.frame2);
            }
        }
        else if (type == RUN_FRAME3) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame3IsLoaded) {
                SDL_DestroyTexture(info.animaion.run.frame3);
            }
        }
        else if (type == RUN_FRAME4) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame4IsLoaded) {
                SDL_DestroyTexture(info.animaion.run.frame4);
            }
        }
        else if (type == RUN_FRAME5) {
            if (info.animaion.runIsLoaded || info.allAnimationsAreLoaded || info.animaion.run.frame5IsLoaded) {
                SDL_DestroyTexture(info.animaion.run.frame5);
            }
        }
        else if (type == RUN) {
            if (info.animaion.runIsLoaded || (info.animaion.run.frame1IsLoaded &&
                                              info.animaion.run.frame2IsLoaded &&
                                              info.animaion.run.frame3IsLoaded &&
                                              info.animaion.run.frame4IsLoaded &&
                                              info.animaion.run.frame5IsLoaded )){
                SDL_DestroyTexture(info.animaion.run.frame1);
                SDL_DestroyTexture(info.animaion.run.frame2);
                SDL_DestroyTexture(info.animaion.run.frame3);
                SDL_DestroyTexture(info.animaion.run.frame4);
                SDL_DestroyTexture(info.animaion.run.frame5);
            }
        }
        // Card Frames
        // Red Card
        else if (type == CARD_RED_FRAME1) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame1IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.red.frame1);
            }
        }
        else if (type == CARD_RED_FRAME2) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame2IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.red.frame2);
            }
        }
        else if (type == CARD_RED_FRAME3) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame3IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.red.frame3);
            }
        }
        else if (type == CARD_RED_FRAME4) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame4IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.red.frame4);
            }
        }
        else if (type == CARD_RED_FRAME5) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame5IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.red.frame5);
            }
        }
        else if (type == CARD_RED_FRAME6) {
            if (info.animaion.card.redIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.red.frame6IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.red.frame6);
            }
        }
        else if (type == CARD_RED) {
            if (info.animaion.card.redIsLoaded || (info.animaion.card.red.frame1IsLoaded &&
                                                   info.animaion.card.red.frame2IsLoaded &&
                                                   info.animaion.card.red.frame3IsLoaded &&
                                                   info.animaion.card.red.frame4IsLoaded &&
                                                   info.animaion.card.red.frame5IsLoaded &&
                                                   info.animaion.card.red.frame6IsLoaded )){
                SDL_DestroyTexture(info.animaion.card.red.frame1);
                SDL_DestroyTexture(info.animaion.card.red.frame2);
                SDL_DestroyTexture(info.animaion.card.red.frame3);
                SDL_DestroyTexture(info.animaion.card.red.frame4);
                SDL_DestroyTexture(info.animaion.card.red.frame5);
                SDL_DestroyTexture(info.animaion.card.red.frame6);
            }
        }
        // Yellow Card
        else if (type == CARD_YELLOW_FRAME1) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame1IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.yellow.frame1);
            }
        }
        else if (type == CARD_YELLOW_FRAME2) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame2IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.yellow.frame2);
            }
        }
        else if (type == CARD_YELLOW_FRAME3) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame3IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.yellow.frame3);
            }
        }
        else if (type == CARD_YELLOW_FRAME4) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame4IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.yellow.frame4);
            }
        }
        else if (type == CARD_YELLOW_FRAME5) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame5IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.yellow.frame5);
            }
        }
        else if (type == CARD_YELLOW_FRAME6) {
            if (info.animaion.card.yellowIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.yellow.frame6IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.yellow.frame6);
            }
        }
        else if (type == CARD_YELLOW) {
            if (info.animaion.card.yellowIsLoaded || (info.animaion.card.yellow.frame1IsLoaded &&
                                                      info.animaion.card.yellow.frame2IsLoaded &&
                                                      info.animaion.card.yellow.frame3IsLoaded &&
                                                      info.animaion.card.yellow.frame4IsLoaded &&
                                                      info.animaion.card.yellow.frame5IsLoaded &&
                                                      info.animaion.card.yellow.frame6IsLoaded )){
                SDL_DestroyTexture(info.animaion.card.yellow.frame1);
                SDL_DestroyTexture(info.animaion.card.yellow.frame2);
                SDL_DestroyTexture(info.animaion.card.yellow.frame3);
                SDL_DestroyTexture(info.animaion.card.yellow.frame4);
                SDL_DestroyTexture(info.animaion.card.yellow.frame5);
                SDL_DestroyTexture(info.animaion.card.yellow.frame6);
            }
        }
        // White Card
        else if (type == CARD_WHITE_FRAME1) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame1IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.white.frame1);
            }
        }
        else if (type == CARD_WHITE_FRAME2) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame2IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.white.frame2);
            }
        }
        else if (type == CARD_WHITE_FRAME3) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame3IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.white.frame3);
            }
        }
        else if (type == CARD_WHITE_FRAME4) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame4IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.white.frame4);
            }
        }
        else if (type == CARD_WHITE_FRAME5) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame5IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.white.frame5);
            }
        }
        else if (type == CARD_WHITE_FRAME6) {
            if (info.animaion.card.whiteIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.white.frame6IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.white.frame6);
            }
        }
        else if (type == CARD_WHITE) {
            if (info.animaion.card.whiteIsLoaded || (info.animaion.card.white.frame1IsLoaded &&
                                                     info.animaion.card.white.frame2IsLoaded &&
                                                     info.animaion.card.white.frame3IsLoaded &&
                                                     info.animaion.card.white.frame4IsLoaded &&
                                                     info.animaion.card.white.frame5IsLoaded &&
                                                     info.animaion.card.white.frame6IsLoaded )){
                SDL_DestroyTexture(info.animaion.card.white.frame1);
                SDL_DestroyTexture(info.animaion.card.white.frame2);
                SDL_DestroyTexture(info.animaion.card.white.frame3);
                SDL_DestroyTexture(info.animaion.card.white.frame4);
                SDL_DestroyTexture(info.animaion.card.white.frame5);
                SDL_DestroyTexture(info.animaion.card.white.frame6);
            }
        }
        // Blue Card
        else if (type == CARD_BLUE_FRAME1) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame1IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.blue.frame1);
            }
        }
        else if (type == CARD_BLUE_FRAME2) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame2IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.blue.frame2);
            }
        }
        else if (type == CARD_BLUE_FRAME3) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame3IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.blue.frame3);
            }
        }
        else if (type == CARD_BLUE_FRAME4) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame4IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.blue.frame4);
            }
        }
        else if (type == CARD_BLUE_FRAME5) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame5IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.blue.frame5);
            }
        }
        else if (type == CARD_BLUE_FRAME6) {
            if (info.animaion.card.blueIsLoaded || info.allAnimationsAreLoaded || info.animaion.card.blue.frame6IsLoaded) {
                SDL_DestroyTexture(info.animaion.card.blue.frame6);
            }
        }
        else if (type == CARD_BLUE) {
            if (info.animaion.card.blueIsLoaded || (info.animaion.card.blue.frame1IsLoaded &&
                                                    info.animaion.card.blue.frame2IsLoaded &&
                                                    info.animaion.card.blue.frame3IsLoaded &&
                                                    info.animaion.card.blue.frame4IsLoaded &&
                                                    info.animaion.card.blue.frame5IsLoaded &&
                                                    info.animaion.card.blue.frame6IsLoaded )){
                SDL_DestroyTexture(info.animaion.card.blue.frame1);
                SDL_DestroyTexture(info.animaion.card.blue.frame2);
                SDL_DestroyTexture(info.animaion.card.blue.frame3);
                SDL_DestroyTexture(info.animaion.card.blue.frame4);
                SDL_DestroyTexture(info.animaion.card.blue.frame5);
                SDL_DestroyTexture(info.animaion.card.blue.frame6);
            }
        }
        else if (type == CARD || type == CARDS) {
            if (
                /* Blue Cards: */
                (info.animaion.card.blueIsLoaded ||   (info.animaion.card.blue.frame1IsLoaded   &&
                                                       info.animaion.card.blue.frame2IsLoaded   &&
                                                       info.animaion.card.blue.frame3IsLoaded   &&
                                                       info.animaion.card.blue.frame4IsLoaded   &&
                                                       info.animaion.card.blue.frame5IsLoaded   &&
                                                       info.animaion.card.blue.frame6IsLoaded   ))
                &&
                /* White Cards: */
                (info.animaion.card.whiteIsLoaded ||  (info.animaion.card.white.frame1IsLoaded  &&
                                                       info.animaion.card.white.frame2IsLoaded  &&
                                                       info.animaion.card.white.frame3IsLoaded  &&
                                                       info.animaion.card.white.frame4IsLoaded  &&
                                                       info.animaion.card.white.frame5IsLoaded  &&
                                                       info.animaion.card.white.frame6IsLoaded  ))
                &&
                /* Yellow Cards: */
                (info.animaion.card.yellowIsLoaded || (info.animaion.card.yellow.frame1IsLoaded &&
                                                       info.animaion.card.yellow.frame2IsLoaded &&
                                                       info.animaion.card.yellow.frame3IsLoaded &&
                                                       info.animaion.card.yellow.frame4IsLoaded &&
                                                       info.animaion.card.yellow.frame5IsLoaded &&
                                                       info.animaion.card.yellow.frame6IsLoaded ))
                &&
                /* Red Cards: */
                (info.animaion.card.redIsLoaded ||    (info.animaion.card.red.frame1IsLoaded    &&
                                                       info.animaion.card.red.frame2IsLoaded    &&
                                                       info.animaion.card.red.frame3IsLoaded    &&
                                                       info.animaion.card.red.frame4IsLoaded    &&
                                                       info.animaion.card.red.frame5IsLoaded    &&
                                                       info.animaion.card.red.frame6IsLoaded    ))
                )
            {
                /* Red Card Frames: */
                SDL_DestroyTexture(info.animaion.card.red.frame1);
                SDL_DestroyTexture(info.animaion.card.red.frame2);
                SDL_DestroyTexture(info.animaion.card.red.frame3);
                SDL_DestroyTexture(info.animaion.card.red.frame4);
                SDL_DestroyTexture(info.animaion.card.red.frame5);
                SDL_DestroyTexture(info.animaion.card.red.frame6);
                
                /* Yellow Card Frames: */
                SDL_DestroyTexture(info.animaion.card.yellow.frame1);
                SDL_DestroyTexture(info.animaion.card.yellow.frame2);
                SDL_DestroyTexture(info.animaion.card.yellow.frame3);
                SDL_DestroyTexture(info.animaion.card.yellow.frame4);
                SDL_DestroyTexture(info.animaion.card.yellow.frame5);
                SDL_DestroyTexture(info.animaion.card.yellow.frame6);
                
                /* White Card Frames: */
                SDL_DestroyTexture(info.animaion.card.white.frame1);
                SDL_DestroyTexture(info.animaion.card.white.frame2);
                SDL_DestroyTexture(info.animaion.card.white.frame3);
                SDL_DestroyTexture(info.animaion.card.white.frame4);
                SDL_DestroyTexture(info.animaion.card.white.frame5);
                SDL_DestroyTexture(info.animaion.card.white.frame6);
                
                /* Blue Card Frames: */
                SDL_DestroyTexture(info.animaion.card.blue.frame1);
                SDL_DestroyTexture(info.animaion.card.blue.frame2);
                SDL_DestroyTexture(info.animaion.card.blue.frame3);
                SDL_DestroyTexture(info.animaion.card.blue.frame4);
                SDL_DestroyTexture(info.animaion.card.blue.frame5);
                SDL_DestroyTexture(info.animaion.card.blue.frame6);
            }
        }
        else if (type == ALL) {
            if ((
                /* Blue card: */
                (info.animaion.card.blueIsLoaded ||  (info.animaion.card.blue.frame1IsLoaded  &&
                                                      info.animaion.card.blue.frame2IsLoaded  &&
                                                      info.animaion.card.blue.frame3IsLoaded  &&
                                                      info.animaion.card.blue.frame4IsLoaded  &&
                                                      info.animaion.card.blue.frame5IsLoaded  &&
                                                      info.animaion.card.blue.frame6IsLoaded  ))
                &&
                /* Walk: */
                (info.animaion.walkIsLoaded ||       (info.animaion.walk.frame1IsLoaded       &&
                                                      info.animaion.walk.frame2IsLoaded       &&
                                                      info.animaion.walk.frame3IsLoaded       &&
                                                      info.animaion.walk.frame4IsLoaded       &&
                                                      info.animaion.walk.frame5IsLoaded       ))
                &&
                /* Run: */
                (info.animaion.runIsLoaded ||        (info.animaion.run.frame1IsLoaded        &&
                                                      info.animaion.run.frame2IsLoaded        &&
                                                      info.animaion.run.frame3IsLoaded        &&
                                                      info.animaion.run.frame4IsLoaded        &&
                                                      info.animaion.run.frame5IsLoaded        ))
                &&
                /* Red Card: */
                (info.animaion.card.redIsLoaded ||   (info.animaion.card.red.frame1IsLoaded   &&
                                                      info.animaion.card.red.frame2IsLoaded   &&
                                                      info.animaion.card.red.frame3IsLoaded   &&
                                                      info.animaion.card.red.frame4IsLoaded   &&
                                                      info.animaion.card.red.frame5IsLoaded   &&
                                                      info.animaion.card.red.frame6IsLoaded   ))
                &&
                /* White Card: */
                (info.animaion.card.whiteIsLoaded || (info.animaion.card.white.frame1IsLoaded &&
                                                      info.animaion.card.white.frame2IsLoaded &&
                                                      info.animaion.card.white.frame3IsLoaded &&
                                                      info.animaion.card.white.frame4IsLoaded &&
                                                      info.animaion.card.white.frame5IsLoaded &&
                                                      info.animaion.card.white.frame6IsLoaded ))
                &&
                /* Blue Card: */
                (info.animaion.card.blueIsLoaded ||  (info.animaion.card.blue.frame1IsLoaded  &&
                                                      info.animaion.card.blue.frame2IsLoaded  &&
                                                      info.animaion.card.blue.frame3IsLoaded  &&
                                                      info.animaion.card.blue.frame4IsLoaded  &&
                                                      info.animaion.card.blue.frame5IsLoaded  &&
                                                      info.animaion.card.blue.frame6IsLoaded  ))
                )
                ||
                info.allAnimationsAreLoaded
                )
            {
                /* Walk Frames: */
                SDL_DestroyTexture(info.animaion.walk.frame1);
                SDL_DestroyTexture(info.animaion.walk.frame2);
                SDL_DestroyTexture(info.animaion.walk.frame3);
                SDL_DestroyTexture(info.animaion.walk.frame4);
                SDL_DestroyTexture(info.animaion.walk.frame5);
                
                /* Run Frames: */
                SDL_DestroyTexture(info.animaion.run.frame1);
                SDL_DestroyTexture(info.animaion.run.frame2);
                SDL_DestroyTexture(info.animaion.run.frame3);
                SDL_DestroyTexture(info.animaion.run.frame4);
                SDL_DestroyTexture(info.animaion.run.frame5);
                
                /* Red Card Frames: */
                SDL_DestroyTexture(info.animaion.card.red.frame1);
                SDL_DestroyTexture(info.animaion.card.red.frame2);
                SDL_DestroyTexture(info.animaion.card.red.frame3);
                SDL_DestroyTexture(info.animaion.card.red.frame4);
                SDL_DestroyTexture(info.animaion.card.red.frame5);
                SDL_DestroyTexture(info.animaion.card.red.frame6);
                
                /* Yellow Card Frames: */
                SDL_DestroyTexture(info.animaion.card.yellow.frame1);
                SDL_DestroyTexture(info.animaion.card.yellow.frame2);
                SDL_DestroyTexture(info.animaion.card.yellow.frame3);
                SDL_DestroyTexture(info.animaion.card.yellow.frame4);
                SDL_DestroyTexture(info.animaion.card.yellow.frame5);
                SDL_DestroyTexture(info.animaion.card.yellow.frame6);
                
                /* White Card Frames: */
                SDL_DestroyTexture(info.animaion.card.white.frame1);
                SDL_DestroyTexture(info.animaion.card.white.frame2);
                SDL_DestroyTexture(info.animaion.card.white.frame3);
                SDL_DestroyTexture(info.animaion.card.white.frame4);
                SDL_DestroyTexture(info.animaion.card.white.frame5);
                SDL_DestroyTexture(info.animaion.card.white.frame6);
                
                /* Blue Card Frames: */
                SDL_DestroyTexture(info.animaion.card.blue.frame1);
                SDL_DestroyTexture(info.animaion.card.blue.frame2);
                SDL_DestroyTexture(info.animaion.card.blue.frame3);
                SDL_DestroyTexture(info.animaion.card.blue.frame4);
                SDL_DestroyTexture(info.animaion.card.blue.frame5);
                SDL_DestroyTexture(info.animaion.card.blue.frame6);
            }
        }
        else {
            if (debugMode)
            error("Error not a valid type! (Tried to unload texture)\n");
        }
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
        if (type == NORMAL) {
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
        info.rect.x = x * pixelsPerGamePixels;
        info.rect.y = y * pixelsPerGamePixels;
    }
    
    void move(moveType type) {
        if (type == UP) {
            goTo(info.rect.x/pixelsPerGamePixels, info.rect.y/pixelsPerGamePixels-1);
        }
        else if (type == DOWN) {
            goTo(info.rect.x/pixelsPerGamePixels, info.rect.y/pixelsPerGamePixels+1);
        }
        else if (type == LEFT) {
            goTo(info.rect.x/pixelsPerGamePixels-1, info.rect.y/pixelsPerGamePixels);
        }
        else if (type == RIGHT) {
            goTo(info.rect.x/pixelsPerGamePixels+1, info.rect.y/pixelsPerGamePixels);
        }
    }
};

class field {
public:
    fieldSprite info;
    animationType currentFieldType = NONE;
    string spriteName;
    
    void init(string importedSpriteName) {
        spriteName = importedSpriteName;
        goTo(0, 0);
    }
    
    void goTo(int x, int y) {
        info.rect.x = x * pixelsPerGamePixels;
        info.rect.y = y * pixelsPerGamePixels;
    }
    
    void load(string pathToFile, fieldType type) {
        if (type == DEBUG_FIELD) {
            info.textures.debug.normal = IMG_LoadTexture(renderer, pathToFile.c_str());
        }
    }
    
    void unload(fieldType type) {
        if (type == DEBUG_FIELD) {
            SDL_DestroyTexture(info.textures.debug.normal);
        }
    }
    
    void display(fieldType type) {
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
            imgH = 0;
            imgW = 0;
        }
        info.rect.h = imgH * pixelsPerGamePixels;
        info.rect.w = imgW * pixelsPerGamePixels;
    }
};

/*-----------------------------------------------------------------
  -----------------------------int Main----------------------------
  -----------------------------------------------------------------*/

int main() {
#if defined(__APPLE__)
    string operatingSystem = "Apple";
#elif defined(__linux__)
    string operatingSystem = "Linux";
#elif defined(_WIN32)
    string operatingSystem = "Windows";
#else
    error("Operating System not allowed.\nError\n\nPlease Contact: yuel.cheong@gmail.com");
    return -1;
#endif
    if (debugMode)
        cout << "Operating System: " << operatingSystem << endl;
    
    
    /*-----------------------------------------------
     -----------------Load Window-------------------
     -----------------------------------------------*/
    
    if (debugMode)
        cout << "Initializing..." << endl;
    
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  /* Pixel-perfect rendering */
    
    /* Width: 444, Height: 690 (Height is automaticly caculated by the function) */
    rectangle screenSize = getScreenSize(444);
    pixelsPerGamePixels = screenSize.pixels;
    if (debugMode) {
        cout << endl << "-----------------------------------------------" << endl << endl;

        cout << "Screen Size: " << screenSize.originalWidth << " x " << screenSize.originalHeight << endl;
        cout << "Window Size: " << screenSize.width << " x " << screenSize.height << endl;
        cout << "Game Size:   " << screenSize.gameWidth << " x " << screenSize.gameHeight << endl;
        cout << "Pixels: " << screenSize.pixels << endl;
    }
    
    string windowName = "Retro Cup | vAlpha 0.1.2 | Last updated: 3/1/2026";
    
    window = SDL_CreateWindow(windowName.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screenSize.width, screenSize.height, SDL_WINDOW_SHOWN);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE); /* SDL_RENDERER_ACCELERATED */
    
    /*-----------------------------------------------
      -----------------Loaded Window-----------------
      -----------------------------------------------*/
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  /* Add this BEFORE creating textures */
    /*
     Load sprites:
     */
    
    field debugSprite;
    debugSprite.init("debugSprite");
    debugSprite.load("/Users/yec/Documents/Retro Cup/Retro Cup/.assets/field/debugField.png", DEBUG_FIELD);
    
    human debugPlayer;
    debugPlayer.init("debugPlayer");
    debugPlayer.loadAnimation(vector<string> {"/Users/yec/Documents/Retro Cup/Retro Cup/.assets/players/debugPlayer.png"}, NORMAL);
        
    bool WindowShouldClose = false;
    SDL_Event event;
    int loopNumber = 0;
    bool IsPrintLoop = false;
    int mouseX = 0;
    int mouseY = 0;
    
    /*
     |----------------|
     |Entering loop...|
     |________________|
     */
    
    while (!WindowShouldClose) {
        loopNumber += 1;
        if (debugMode)
        IsPrintLoop = isCommonMultiple(loopNumber,120);
        /* Only shows every 120 loops */
        if (IsPrintLoop)
            cout <<
            "---------------------------------------------------------------\n" <<
            "---------------Loop #" << loopNumber << "---------------------\n" <<
            "---------------------------------------------------------------\n";
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) WindowShouldClose = true;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.type == SDLK_w) {
                    debugPlayer.move(UP);
                    print("Key detected! UP\n");
                }
                if (event.key.type == SDLK_a) {
                    debugPlayer.move(LEFT);
                    print("Key detected! LEFT\n");
                }
                if (event.key.type == SDLK_s) {
                    debugPlayer.move(DOWN);
                    print("Key detected! DOWN\n");
                }
                if (event.key.type == SDLK_d) {
                    debugPlayer.move(RIGHT);
                    print("Key detected! RIGHT\n");
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
                    cout << "Clicked at: " << mouseX << ", " << mouseY << "\n";
                }
            }
        }
        if (isCommonMultiple(loopNumber,120)) {
            if (debugMode)
            cout << "Mouse position: " << mouseX << "," << mouseY << "\n";
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); /* Make the opacity max */
        SDL_RenderClear(renderer); /* Clear the screen  */
        /* Rendering Each Sprite: */
        debugSprite.display(DEBUG_FIELD);
        debugPlayer.move(RIGHT);
        debugPlayer.move(DOWN);
        debugPlayer.display(NORMAL);
        
        SDL_RenderPresent(renderer);
    }
    if (debugMode)
    cout << "Exited loop...\n";
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    debugSprite.unload(DEBUG_FIELD);
    
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
