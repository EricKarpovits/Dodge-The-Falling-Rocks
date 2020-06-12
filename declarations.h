// Libraries, header files
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <time.h>
#include <windows.h>

// Colours
#define PINK        al_map_rgb(255, 0, 255)
#define BLACK       al_map_rgb(0, 0, 0)
#define SLATEGREY   al_map_rgb(112,128,144)
#define RED         al_map_rgb(255, 0, 0)
#define WHITE	    al_map_rgb(255, 255, 255)

// Define Constants
#define NUMBER_OF_ROCKS 20
#define NUMBER_OF_LIVES 5
#define NUMBER_OF_HIGHSCORES 5
#define NUMBER_OF_POWERUPS 2
#define NUMBER_OF_BUTTONS 4
#define NUMBER_OF_MUSIC_SAMPLES 4
#define FPS 30
#define SCREEN_WIDTH 620
#define SCREEN_HEIGHT 800
#define GENERATE_RANGE 570

// Error Code Constants
#define ERROR_DISPLAY -1
#define ERROR_KEYBOARD -2
#define ERROR_CHARACTER_IMG -3
#define ERROR_IMG_ADDON -4
#define ERROR_PRIMATIVE_ADDON -5
#define ERROR_MOUSE_ADDON -6
#define ERROR_FPSTIMER -7
#define ERROR_INVINCIBLE_TIMER -8
#define ERROR_SLOW_MOTION_TIMER -9
#define ERROR_TINY_TIMER -10
#define ERROR_SPEED_INCREASER_TIMER -11
#define ERROR_EVENT_QUEUE -12
#define ERROR_ARIAL_FONT -13
#define ERROR_SMALL_ARIAL_FONT -14
#define ERROR_ROCK_IMG -15
#define ERROR_LIFE_IMG -16
#define ERROR_INVINCIBILITY_IMG -17
#define ERROR_SLOW_MOTION_IMG -18
#define ERROR_MINI_IMG -19
#define ERROR_FONT_ADDON -20
#define ERROR_TTF_ADDON -21
#define ERROR_ALLEGRO -22
#define ERROR_IMAGE_ADDON -23
#define ERROR_INSTALL_AUDIO -24
#define ERROR_ACODEC_ADDON -25
#define ERROR_MUSIC_FILE_COLLISION -26
#define ERROR_MUSIC_FILE_GAMEMUSIC -27
#define ERROR_MUSIC_FILE_BUTTONCLICK -28
#define ERROR_MUSIC_FILE_CHARACTER_DEATH -29
#define ERROR_POWERUP_IMG -30
#define ERROR_MINI_CHARACTER_IMG -31
#define ERROR_HURT_CHARACTER_IMG -32
#define ERROR_LOAD_FPTR -33
#define ERROR_DISPLAY_TIMER -34

// Game Mode Constants
#define START_MENU 1
#define INSTRUCTIONS 2
#define GAME_ON 3
#define CREDITS 4
#define HIGHSCORE 5
#define PAUSED 6

// Object Constants
#define CHARACTER 1
#define ROCKS 2
#define POWER_UPS 3
#define LIVES 4

// Set up structs
struct Character {
    ALLEGRO_BITMAP *bitmap;
    int characterPositionX;
    int characterPositionY;
    int bbRight, bbLeft, bbTop, bbBottom;
    bool drawCharacterHit;
};

struct Rocks {
    ALLEGRO_BITMAP *bitmap;
    int rockPositionX;
    int rockPositionY;
    int bbRight, bbLeft, bbTop, bbBottom;
};

struct Lives {
    ALLEGRO_BITMAP *bitmap;
    bool usable;
    int xCoordinate;
    int yCoordinate;
};

struct PowerUp {
    ALLEGRO_BITMAP *bitmap;

    int powerupXCoordinate;
    int powerupYCoordinate;
    bool collision;

    int bbRight, bbLeft, bbTop, bbBottom;

    // Power up Type
    bool powerUpMini;
    bool powerUpSlowmo;
    bool powerUpInvincibility;
};

struct Keyboard {
    bool keyUp;
    bool keyDown;
    bool keyLeft;
    bool keyRight;
    bool keySpace;
    bool keyB;
    bool keyR;
    bool keyP;
    int xCoordinateMovement;
    int yCoordinateMovement;
};

struct Button {
    int upperLeftXCoordinate, upperLeftYCoordinate, lowerRightXCoordinate, lowerRightYCoordinate;
    bool clicked;
    bool filled;
};

struct InstructionImages {
    ALLEGRO_BITMAP *arrowKeys, *tinyPowerUp, *slowMotionPowerUp, *invinciblePowerUp;
};

struct Paused {
    bool slowmoTimer, invincibleTimer, miniTimer, speedIncreaser;
};

struct Application {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_TIMER *timer, *speedIncreaser, *slowmoTimer, *invincibleTimer, *miniTimer, *displayTimer;
    ALLEGRO_FONT *arial, *smallArial;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_SAMPLE *gameMusic, *buttonClick, *characterDeath, *collision;
};
