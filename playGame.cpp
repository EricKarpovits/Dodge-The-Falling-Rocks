#include "declarations.h"

extern ALLEGRO_TIMER *slowmoTimer, *invincibleTimer, *miniTimer, *speedIncreaser, *timer;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_FONT *arial;

/**
* Main function of the game
* It allows every game mode to run and the user to play the game
* return game exit code
**/
int playGame(bool &continuePlaying,  Keyboard &userKeyboard, Character &mainCharacter, Rocks fallingRocks[], Lives userLives[], PowerUp fallingPowerUps[], int &gameMode, Button clickableButton[], Paused &timerPaused){

    // Declare variables and create an event
    int returnCode;
    bool buttonClicked, keyDown;
    static int numberOfCollisions = 0;
    static int userScore = 0;

    ALLEGRO_EVENT ev;

    al_wait_for_event(event_queue, &ev);

    switch (gameMode) {
        case START_MENU:
            drawButtons(clickableButton, gameMode);
            al_draw_text(arial, BLACK, 0, 773, 0, "By Eric Karpovits");
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "Dodge the Falling Rocks");
            al_flip_display();
            break;
        case INSTRUCTIONS:
            drawButtons(clickableButton, gameMode);
            returnCode = gameInstructions();
            if (returnCode != 0){
                printf("Returning error code %d", returnCode);
                return returnCode;
            }
            al_flip_display();
            break;
        case GAME_ON:
            al_start_timer(speedIncreaser);
            // Restart the game if the user presses R
            if(userKeyboard.keyR){
                setupMain(mainCharacter, userLives, fallingRocks, userKeyboard, fallingPowerUps);
                userScore = 0;
                numberOfCollisions = 0;
            }

            if(timerPaused.invincibleTimer || timerPaused.miniTimer || timerPaused.slowmoTimer || timerPaused.speedIncreaser){
                unpauseTimers(timerPaused);
            }

            // Event timer
            if (ev.type == ALLEGRO_EVENT_TIMER) {

                // This is an if statement which does not allow any movement to occur
                if(userKeyboard.keyP){
                    gameMode = PAUSED;
                    buttonSetup(clickableButton, gameMode);
                    userKeyboard.keyP = false;
                    pauseTimers(timerPaused);
                }
                // Set dx and dy so the character will do what the keyboard tells it
                keyboardMovement(userKeyboard);
                // Sprite movement
                spriteMovement(mainCharacter, userKeyboard, fallingRocks, fallingPowerUps);

                drawButtons(clickableButton, gameMode);

                drawSprites(mainCharacter, fallingRocks, userLives, fallingPowerUps);

                // Check if rocks gave reached bottom and print out the score
                userScore += checkIfObjectReachedBottom(fallingRocks, fallingPowerUps);
                al_draw_textf(arial, RED, 620, 0, ALLEGRO_ALIGN_RIGHT, "Score %d", userScore);

                // Inform the user what level they are on
                userLevel();

                // Calculate bounding boxes
                obtainBoundingBoxes(mainCharacter, fallingRocks, fallingPowerUps);

                // Draw a flicking collision image
                returnCode = collisionsMain(mainCharacter, fallingRocks, numberOfCollisions, userLives, fallingPowerUps);
                if (returnCode != 0) {
                    printf("Returning error code %d.", returnCode);
                    return returnCode;
                }


                if(!userLives[0].usable){
                    gameMode = HIGHSCORE;
                }
                // Draw bounding boxes if user presses the character B
                drawBoundingBox(mainCharacter, fallingRocks, userKeyboard, fallingPowerUps);

                // Check if the power timer is up
                returnCode = checkIfPowerUpOver(mainCharacter);
                if (returnCode != 0) {
                    printf("Returning error code %d.", returnCode);
                    return returnCode;
                }
            }
            break;
        case CREDITS:
            drawButtons(clickableButton, gameMode);
            returnCode = credits();
            if (returnCode != 0){
                return returnCode;
            }
            break;
        case HIGHSCORE:
            returnCode = checkHighScore(userScore);
            if (returnCode != 0){
                return returnCode;
            }
            userKeyboard.keyR = true;
            gameMode = START_MENU;
            buttonSetup(clickableButton, gameMode);
            break;
        case PAUSED:
            drawButtons(clickableButton, gameMode);
            al_flip_display();
            if (userKeyboard.keyP){
                gameMode = GAME_ON;
                userKeyboard.keyP = false;
                buttonSetup(clickableButton, gameMode);
            }
            break;
        default:
            break;
    }
    // Checks if the user closed the display
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        continuePlaying = false;
    }
    // Set direction if key pressed
    else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        keyDown = true;
        keyboardEvent(ev.keyboard.keycode, userKeyboard, keyDown);
    // Stop movement if key is released
    } else if (ev.type == ALLEGRO_EVENT_KEY_UP){
        keyDown = false;
        keyboardEvent(ev.keyboard.keycode, userKeyboard, keyDown);
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        buttonClicked = true;
        checkWhichButtonAction(clickableButton, ev.mouse.x, ev.mouse.y, gameMode, buttonClicked);
        checkButtonState(clickableButton, gameMode, continuePlaying, userKeyboard, timerPaused);
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES){
        buttonClicked = false;
        checkWhichButtonAction(clickableButton, ev.mouse.x, ev.mouse.y, gameMode, buttonClicked);
    }

    return  0;
}

// This function checks to see if the rock reached the bottom to reset it and add a point for the player
int checkIfObjectReachedBottom(Rocks rocksReachedBottom[], PowerUp powerUpReachedBottom[]){
    int scoreIncrease = 0;
    for(int i = 0; i < NUMBER_OF_ROCKS; i++){
        if(rocksReachedBottom[i].rockPositionY >= 800){
           rocksReachedBottom[i].rockPositionY = rand() % 500 - 500;
           rocksReachedBottom[i].rockPositionX = rand() % GENERATE_RANGE;
           scoreIncrease ++;
        }
    }
    for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
        if(powerUpReachedBottom[i].powerupYCoordinate >= 800){
            setupPowerUps(powerUpReachedBottom[i]);
        }
    }

    return scoreIncrease;
}
