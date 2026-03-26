#include <iostream>
#pragma once

using
std::cout,
std::string;

int RandomInt(int low, int high) {
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> distrib(low, high);
    return distrib(gen);
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
        error("Error, could not get screen size due to error: " + (string)SDL_GetError() + "\n");
    }
    
    rectangle builtInScreen;
    builtInScreen.width = displayMode.w;
    builtInScreen.height = displayMode.h;
    printInfo("Built in screen: {" + std::to_string(builtInScreen.width) + "," + std::to_string(builtInScreen.height) + "}\n");
    
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

SDL_Texture* loadTexture(string path) {
    SDL_Texture* raw = IMG_LoadTexture(renderer, path.c_str());
    if (!raw) {
        error("Failed to load texture: " + (string)IMG_GetError() + "\n");
    }
    return raw;
}

void updateFPS() {
    static auto previousTime = std::chrono::high_resolution_clock::now();
    static int frameCount = 0;

    auto currentTime = std::chrono::high_resolution_clock::now();
    frameCount++;

    std::chrono::duration<double> elapsed = currentTime - previousTime;

    // Update the global variable only once per second
    if (elapsed.count() >= 1.0) {
        currentFPS = frameCount / elapsed.count();
        frameCount = 0;
        previousTime = currentTime;
        largestFPSlist.push_back(currentFPS);
    }
}

void foucusWindow() {
    if (operatingSystem == "Apple"){
        SDL_RestoreWindow(window);
        SDL_RaiseWindow(window);
    }
    else {
        if (SDL_SetWindowInputFocus(window) != 0) {
            warrning(std::string("Failed to focus window: ") + SDL_GetError() + "\n");
        }
    }
}

void unmute() {
    muted = false;
    audio.syncMuted();
}

void mute() {
    muted = true;
    audio.syncMuted();
}
