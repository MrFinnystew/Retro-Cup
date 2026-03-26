#pragma once

typedef enum {
    GAME_KEY_NONE,
    // Letters:
    GAME_KEY_A,
    GAME_KEY_B,
    GAME_KEY_C,
    GAME_KEY_D,
    GAME_KEY_E,
    GAME_KEY_F,
    GAME_KEY_G,
    GAME_KEY_H,
    GAME_KEY_I,
    GAME_KEY_J,
    GAME_KEY_K,
    GAME_KEY_L,
    GAME_KEY_M,
    GAME_KEY_N,
    GAME_KEY_O,
    GAME_KEY_P,
    GAME_KEY_Q,
    GAME_KEY_R,
    GAME_KEY_S,
    GAME_KEY_T,
    GAME_KEY_U,
    GAME_KEY_V,
    GAME_KEY_W,
    GAME_KEY_X,
    GAME_KEY_Y,
    GAME_KEY_Z,
    
    // Numbers:
    GAME_KEY_1,
    GAME_KEY_2,
    GAME_KEY_3,
    GAME_KEY_4,
    GAME_KEY_5,
    GAME_KEY_6,
    GAME_KEY_7,
    GAME_KEY_8,
    GAME_KEY_9,
    GAME_KEY_0,
    
    // Arrows:
    GAME_KEY_UP,
    GAME_KEY_DOWN,
    GAME_KEY_LEFT,
    GAME_KEY_RIGHT,
    
    // Other
    GAME_KEY_SPACE,
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
    NONE_BALL,
    
    NORMAL_BALL,
    DEBUG_BALL,
} ballType;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    JUMP,
} moveType;
