/// Prototype

// Setup
int setupMain(Character &cSetup, Lives lSetup[], Rocks rSetup[], Keyboard &kSetup, PowerUp fallingPowerUps[], InstructionImages &iSetup);
void generateRockLocation(Rocks startPosition[]);
void lifeSetup( Lives a[]);
void characterSetup(Character &a);
int loadImage(Character &imageCharacter, Rocks imageRocks[], Lives imageLives[]);
void initializeUserKeyboard(Keyboard &initialize);
int initializeAllegro();
int loadInstructionImg(InstructionImages &i);

// Play Game
int playGame(bool &continuePlaying, Keyboard &userKeyboard, Character &mainCharacter, Rocks fallingRocks[], Lives userLives[], PowerUp fallingPowerUps[], int &gameMode, Button clickableButton[], Paused &timerPaused, InstructionImages &displayImages);
void userLevel();
int checkIfObjectReachedBottom(Rocks rocksReachedBottom[], PowerUp powerUpReachedBottom[]);

// Collisions
int collisionsMain(Character &mainCharacter, Rocks fallingRocks[], int &numberOfCollisions, Lives userLives[], PowerUp fallingPowerUps[]);
int drawInvinciblity(bool &timerRunning, Character &mainCharacter);
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
void exitProgram(Character &image, InstructionImages &displayImages);
int checkHighScore(int playerScore);
void printHighScore(int highScore[]);
int averageHighscore(int playerScore);

// PowerUps
int activatePowerUp(PowerUp &userPowerUps, Character &userCharacter);
int setupPowerUps(PowerUp &powerUpSetup);
void powerUpMain(PowerUp &userPowerUps);
int checkIfPowerUpOver(Character &userCharacter);

// Mouse driven interface
void buttonSetup(Button setup[], int gameMode);
void setButtonCoords(Button &button, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY);
void drawButtons(Button draw[], int gameMode);
void checkWhichButtonAction(Button check[], int mouseXCoordinate, int mouseYCoordinate, int gameMode, bool buttonClicked);
void checkButtonState(Button state[], int &gameMode, bool &continuePlaying, Keyboard &userKeyboard, Paused &timerPaused);
void checkIfNewGameMode(int newGameMode, int previousGameMode, Button b[]);
void pauseTimers(Paused &timerPaused);
void unpauseTimers(Paused &timerPaused);

// Checks
int checkIfFileLoaded(FILE *fptr);

// Application
int gameInstructions(InstructionImages &draw);
int credits();
void printFromTextfile(FILE *fptr);
