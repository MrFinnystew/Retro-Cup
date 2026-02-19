/* Retro Cup Main.cpp
 * ----------------------------- Version information: -----------------------------------------
 
                                      Versions:
 vBeta011 (This version)
 vBeta012 (Current version)
 
 * -----------------------------Last updated: Sat Feb 14 --------------------------------------
 *
 * Notes are set up like C++
 * "{
 *
 * }"
 * This is used to define a section
 *
 * "def"
 * Used when defining something that will be used over and over in this code.
 *
 * Visuals {
 *  SDL2
 *  For more about OpenGL go to OpenGl.com
 * }
 *
 * notesForYu-El {
 *      /Users/yec/Library/Developer/Xcode/DerivedData/Retro_Cup-epucvnkixjmotphfdzpnvcotyiyg/Build/Products/Debug/Retro Cup
 * }
 *
 * Notation {
 *      camelCase
 * }
 *
 * READ THIS BEFORE CODING ON THIS DOCUMENT {
 *  def Sprite{
 *      Sprite stands for a thing on the screen like the the field, the player, or the ref.
 *  }
 * }
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <limits>

// Are using these:
using
std::cout,
std::cin,
std::string,
std::endl,
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
} MoveAnimation;

typedef struct cardAnimation {
    SDL_Texture* frame1;
    SDL_Texture* frame2;
    SDL_Texture* frame3;
    SDL_Texture* frame4;
    SDL_Texture* frame5;
    SDL_Texture* frame6;
} cardAnimation;

typedef struct penaltyCardFrames {
    cardAnimation red;
    cardAnimation yellow;
    cardAnimation white;
    cardAnimation blue;
} penaltyCardFrames;

typedef struct Animation {
    MoveAnimation walk;
    MoveAnimation run;
    penaltyCardFrames card;
} Animation;

typedef struct humanSprite {
    int spriteWidth;
    int spriteHeight;
    string pathToFile;
    string fileName;
    string uiFileName;
    SDL_Texture* Texture;
    SDL_Rect rect;
    bool yellowCard;
    bool redCard;
    bool blueCard;
} humanSprite;

int RandomInt(int low, int high) {
    // 1. Obtain a random seed from the hardware or OS
    //    (intended to be non-deterministic when possible)
    std::random_device rd;
    
    // 2. Initialize a high-quality pseudo-random number engine with the seed
    //    The Mersenne Twister engine (mt19937) is a common choice
    std::mt19937 gen(rd());
    
    // 3. Define the desired range (e.g., between 1 and 100 inclusive)
    //    uniform_int_distribution ensures uniform distribution across the range
    std::uniform_int_distribution<> distrib(low, high);
    
    // 4. Generate and return the random number
    int randomNumber = distrib(gen);
    
    return randomNumber;
}

bool refreshSprite(Sprite) {
    return true;
}

void refreshHuman(humanSprite) {
}

SDL_Texture* createFieldTexture(string pathToFile, SDL_Renderer* renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, pathToFile.c_str());
    
    if (!texture) {
        cout << "Failed to load: " << IMG_GetError() << "\n";
        return nullptr;
    }
    return texture;
}

void betaConvertFieldDimentionsToFullScreen(SDL_Texture* texture, Sprite& sprite) {
    int imgH = sprite.spriteHeight;
    int imgW = sprite.spriteWidth;
    // Get screen size
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;
    
    SDL_QueryTexture(texture, NULL, NULL, &imgW, &imgH);
    cout << "Image: " << imgW << "x" << imgH << "\n";
    
    // Calculate scaled size
    float ratio = (float)imgH / (float)imgW;
    int newW = screenWidth;
    int newH = (int)(screenWidth * ratio);
    int yPos = (screenHeight - newH) / 2;
    
    sprite.rect.w = newW;
    sprite.rect.h = newH;
    sprite.rect.x = 0;
    sprite.rect.y = yPos;
}

void pauseMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void pauseSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

Sprite CreateFullscreenField(string pathToFile, SDL_Window* window, SDL_Renderer* renderer, Sprite& sprite) {
    sprite.Texture = createFieldTexture(pathToFile, renderer);
    int texW = 0, texH = 0;
    SDL_QueryTexture(sprite.Texture, NULL, NULL, &texW, &texH);
    sprite.spriteWidth = texW;
    sprite.spriteHeight = texH;
    sprite.rect = {0, 0, texW, texH};
    betaConvertFieldDimentionsToFullScreen(sprite.Texture, sprite);
    return sprite;
}

Sprite CreatePlayer(string pathToFile, SDL_Renderer* renderer, Sprite& fieldSprite) {
    Sprite playerSprite;
    
    // Load texture
    playerSprite.Texture = IMG_LoadTexture(renderer, pathToFile.c_str());
    
    if (!playerSprite.Texture) {
        cout << "Failed to load player: " << IMG_GetError() << "\n";
        return playerSprite;
    }
    
    // Get original player image dimensions
    int originalPlayerWidth, originalPlayerHeight;
    SDL_QueryTexture(playerSprite.Texture, NULL, NULL, &originalPlayerWidth, &originalPlayerHeight);
    
    // Get original field image dimensions (before scaling)
    int originalFieldWidth, originalFieldHeight;
    SDL_QueryTexture(fieldSprite.Texture, NULL, NULL, &originalFieldWidth, &originalFieldHeight);
    
    // Calculate the field's scale factor (use width scale only to maintain aspect ratio)
    float fieldScale = round((float)fieldSprite.rect.w / (float)originalFieldWidth);
    
    // Apply the same scale to BOTH player dimensions
    int playerWidth = (int)(originalPlayerWidth * fieldScale);
    int playerHeight = (int)(originalPlayerHeight * fieldScale);
    
    // Set up the sprite
    playerSprite.spriteWidth = playerWidth;
    playerSprite.spriteHeight = playerHeight;
    playerSprite.rect = {0, 0, playerWidth, playerHeight};
    playerSprite.pathToFile = pathToFile;
    
    cout << "Player created at matching pixel scale: " << playerWidth << "x" << playerHeight << "\n";
    cout << "Scale factor: " << fieldScale << "x\n";
    
    return playerSprite;
}

void centerSpriteOnField(Sprite& playerSprite, Sprite& fieldSprite) {
    playerSprite.rect.x = fieldSprite.rect.x + (fieldSprite.rect.w / 2) - (playerSprite.rect.w / 2);
    playerSprite.rect.y = fieldSprite.rect.y + (fieldSprite.rect.h / 2) - (playerSprite.rect.h / 2);
}

float getSpriteScale(Sprite& sprite) {
    int originalWidth, originalHeight;
    SDL_QueryTexture(sprite.Texture, NULL, NULL, &originalWidth, &originalHeight);
    
    float scaleX = (float)sprite.rect.w / (float)originalWidth;
    
    return scaleX;  // Returns how many game pixels per image pixel
}

//-----------------------------------------------------------------
//-----------------------------int Main----------------------------
//-----------------------------------------------------------------

int main() {
    //-----------------------------------------------
    //-----------------Load Window-------------------
    //-----------------------------------------------
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  // Pixel-perfect rendering
    
    // Get screen size
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;
    
    cout << "Screen: " << screenWidth << "x" << screenHeight << "\n";
    
    SDL_Window* window = SDL_CreateWindow("Retro Cup | vBeta 0.1.2 | Last updated: 2/16/26",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //-----------------------------------------------
    //-----------------Loaded Window-----------------
    //-----------------------------------------------
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");  // Add this BEFORE creating textures
    
    Sprite debugField = CreateFullscreenField("/Users/yec/Documents/Retro Cup/Retro Cup/.assets/field/debugField/debugField.png", window, renderer, debugField);
    Sprite debugMidfielder = CreatePlayer("/Users/yec/Documents/Retro Cup/Retro Cup/.assets/Players/debugPlayer.png", renderer, debugField);
    centerSpriteOnField(debugMidfielder, debugField);
        
    bool WindowShouldClose = false;
    cout << "Field: " << getSpriteScale(debugField) << "\nPlayer: " << getSpriteScale(debugMidfielder) << endl;
    SDL_Event event;
    int loopNumber = 0;
    int mouseX = 0;
    int mouseY = 0;
    
    while (!WindowShouldClose) {
        loopNumber += 1;
        cout <<
        "---------------------------------------------------------------\n" <<
        "--------------- Loop #" << loopNumber << "---------------------\n" <<
        "---------------------------------------------------------------\n";
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) WindowShouldClose = false;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_UP:
                        debugMidfielder.rect.y -= getSpriteScale(debugField);  // Move up
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        debugMidfielder.rect.y += getSpriteScale(debugField);  // Move down
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        debugMidfielder.rect.x -= getSpriteScale(debugField);  // Move left
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        debugMidfielder.rect.x += getSpriteScale(debugField);  // Move right
                        break;
                    case SDLK_SPACE:
                        cout << "Space pressed!\n";
                        break;
                
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                // Track mouse position
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    cout << "Clicked at: " << mouseX << ", " << mouseY << "\n";
                }
            }
        }
        cout << "Mouse position (x,y):" << mouseX << ", " << mouseY << "\n";
        cout << "";
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, debugField.Texture, NULL, &debugField.rect);
        SDL_RenderCopy(renderer, debugMidfielder.Texture, NULL, &debugMidfielder.rect);
        SDL_RenderPresent(renderer);
    }
    cout << "";
    
    cout << "Destroying images...";
    SDL_DestroyTexture(debugMidfielder.Texture);
    SDL_DestroyTexture(debugField.Texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
