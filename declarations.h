// Libraries, header files
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
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
#define NUMBER_OF_POWERUPS 1
#define NUMBER_OF_BUTTONS 4
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

struct Rocks{
    ALLEGRO_BITMAP *bitmap;
    int rockPositionX;
    int rockPositionY;
    int bbRight, bbLeft, bbTop, bbBottom;
};

struct Lives{
    ALLEGRO_BITMAP *bitmap;
    bool usable;
    int xCoordinate;
    int yCoordinate;
};

struct PowerUp{
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

struct Keyboard{
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

struct Button{
    int upperLeftXCoordinate, upperLeftYCoordinate, lowerRightXCoordinate, lowerRightYCoordinate;
    bool clicked;
    bool filled;
};

struct InstructionImages{
    ALLEGRO_BITMAP *arrowKeys, *tinyPowerUp, *slowMotionPowerUp, *invincibilityPowerUp;
    bool loaded = false;
};

struct Paused{
    bool slowmoTimer, invincibleTimer, miniTimer, speedIncreaser;
};

/// Prototype

// Setup
int setupMain(Character &cSetup, Lives lSetup[], Rocks rSetup[], Keyboard &kSetup, PowerUp fallingPowerUps[]);
void generateRockLocation(Rocks startPosition[]);
void lifeSetup( Lives a[]);
void characterSetup(Character &a);
int loadImage(Character &imageCharacter, Rocks imageRocks[], Lives imageLives[]);
void initializeUserKeyboard(Keyboard &initialize);

// Play Game
int playGame(bool &continuePlaying, Keyboard &userKeyboard, Character &mainCharacter, Rocks fallingRocks[], Lives userLives[], PowerUp fallingPowerUps[], int &gameMode, Button clickableButton[], Paused &timerPaused);
void userLevel();
int checkIfObjectReachedBottom(Rocks rocksReachedBottom[], PowerUp powerUpReachedBottom[]);

// Collisions
int collisionsMain(Character &mainCharacter, Rocks fallingRocks[], int &numberOfCollisions, Lives userLives[], PowerUp fallingPowerUps[]);
int drawCollision(bool &timerRunning, Character &mainCharacter);
void obtainBoundingBoxes(Character &a, Rocks b[], PowerUp c[]);
void calcBoundingBoxes(Character &a, Rocks &b, PowerUp &c, int object);
void drawBoundingBox(Character &image, Rocks object[], Keyboard &userKeyboard, PowerUp powerUpImg[]);
bool checkCollision(Character &a, Rocks &b, PowerUp &c, bool checkCollisionRocks);

// Movement
void spriteMovement(Character &cMovement, Keyboard &kMovement, Rocks rMovement[], PowerUp pMovement[]);
void keyboardMovement(Keyboard &movement);
void keyboardEvent(int keycode, Keyboard &event, bool keyDown);
void drawSprites(Character &cDraw, Rocks rDraw[], Lives lDraw[], PowerUp pDraw[]);
bool checkIfSlowMoActivated(PowerUp checkSlowMo);

// The end of the program
void exitProgram(Character &image);
int checkHighScore(int playerScore);
void printHighScore(int highScore[]);
int averageHighscore(int playerScore);

// PowerUps
int activatePowerUp(PowerUp &userPowerUps, Character &userCharacter);
int setupPowerUps(PowerUp &powerUpSetup);
void powerUpMain(PowerUp &userPowerUps);
int checkIfPowerUpOver(Character &userCharacter);

// Start Menu
void buttonSetup(Button setup[], int gameMode);
void setButtonCoords(Button &button, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY);
void drawButtons(Button draw[], int gameMode);
void checkWhichButtonAction(Button check[], int mouseXCoordinate, int mouseYCoordinate, int gameMode, bool buttonClicked);
void checkButtonState(Button state[], int &gameMode, bool &continuePlaying, Keyboard &userKeyboard, Paused &timerPaused);
int gameInstructions();
int credits();
void checkIfNewGameMode(int newGameMode, int previousGameMode, Button b[]);
void pauseTimers(Paused &timerPaused);
void unpauseTimers(Paused &timerPaused);
void printFromTextfile(FILE *fptr);

