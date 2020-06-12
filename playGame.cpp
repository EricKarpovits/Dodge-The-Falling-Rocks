#include "declarations.h"
#include "prototype.h"

extern Application app;

/**
* Main function of the game
* It allows every game mode to run and the user to play the game
* Need to pass all the object structs and a few variables such as game mode and if the user continues to play
* Returns game exit code as an int. 0 if there are no errors, otherwise refer to the constants for what the error codes mean
**/
int playGame(
        bool &continuePlaying,
        Keyboard &userKeyboard,
        Character &mainCharacter,
        Rocks fallingRocks[],
        Lives userLives[],
        PowerUp fallingPowerUps[],
        int &gameMode,
        Button clickableButton[],
        Paused &timerPaused,
        InstructionImages &displayImages) {

    // Declare variables and create an event
    int returnCode;
    bool buttonClicked, keyDown;
    static int numberOfCollisions = 0;
    static int userScore = 0;
    ALLEGRO_EVENT ev;

    al_wait_for_event(app.event_queue, &ev);

    switch (gameMode) {
        case START_MENU:
            // Draw buttons
            drawButtons(clickableButton, gameMode);
            al_draw_text(app.arial, BLACK, 0, 773, 0, "By Eric Karpovits");
            al_draw_text(app.arial, BLACK, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "Dodge the Falling Rocks");
            al_flip_display();
            break;
        case INSTRUCTIONS:
            // Draw buttons and game instructions
            drawButtons(clickableButton, gameMode);
            returnCode = gameInstructions(displayImages);
            if (returnCode != 0){
                printf("Returning error code %d", returnCode);
                return returnCode;
            }
            al_flip_display();
            break;
        case GAME_ON:
            al_start_timer(app.speedIncreaser);
            // Restart the game if the user presses R
            if(userKeyboard.keyR){
                setupMain(mainCharacter, userLives, fallingRocks, userKeyboard, fallingPowerUps, displayImages);
                userScore = 0;
                numberOfCollisions = 0;
            }

            // Check if the timers were paused to unpause
            if (timerPaused.invincibleTimer || timerPaused.miniTimer || timerPaused.slowmoTimer || timerPaused.speedIncreaser) {
                unpauseTimers(timerPaused);
            }

            // Event timer
            if (ev.type == ALLEGRO_EVENT_TIMER) {

                // Set dx and dy so the character will do what the keyboard tells it
                keyboardMovement(userKeyboard);
                // Sprite movement
                spriteMovement(mainCharacter, userKeyboard, fallingRocks, fallingPowerUps);

                // Draw buttons and sprites
                drawButtons(clickableButton, gameMode);
                drawSprites(mainCharacter, fallingRocks, userLives, fallingPowerUps);

                // Check if rocks gave reached bottom and print out the score
                userScore += checkIfObjectReachedBottom(fallingRocks, fallingPowerUps);
                al_draw_textf(app.arial, RED, 620, 0, ALLEGRO_ALIGN_RIGHT, "Score %d", userScore);

                // Inform the user what level they are on
                userLevel();

                // Calculate bounding boxes
                obtainBoundingBoxes(mainCharacter, fallingRocks, fallingPowerUps);

                // Draw a flicking collision image
                returnCode = collisionsMain(mainCharacter, fallingRocks, numberOfCollisions, userLives, fallingPowerUps);
                if (returnCode != 0) {
                    return returnCode;
                }

                // Check if the user has no more lives and play death sound
                if (!userLives[4].usable) {
                    al_play_sample(app.characterDeath, 5.0, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
                    gameMode = HIGHSCORE;
                }
                // Draw bounding boxes if user presses the character B
                drawBoundingBox(mainCharacter, fallingRocks, userKeyboard, fallingPowerUps);

                // Check if the power timer is up
                returnCode = checkIfPowerUpOver(mainCharacter);
                if (returnCode != 0) {
                    return returnCode;
                }

                // This is an if statement which does not allow any movement to occur
                if (userKeyboard.keyP) {
                    gameMode = PAUSED;
                    buttonSetup(clickableButton, gameMode);
                    userKeyboard.keyP = false;
                    pauseTimers(timerPaused);
                }

            }
            break;
        case CREDITS:
            // Draw buttons and credits
            drawButtons(clickableButton, gameMode);
            returnCode = credits();
            if (returnCode != 0) {
                return returnCode;
            }
            break;
        case HIGHSCORE:
            // Check if the user obtained a high score and inform them the average overall score
            returnCode = checkHighScore(userScore);
            if (returnCode != 0) {
                return returnCode;
            }
            userKeyboard.keyR = true;
            gameMode = START_MENU;
            buttonSetup(clickableButton, gameMode);
            Sleep(8000);
            break;
        case PAUSED:
            // Draw buttons
            drawButtons(clickableButton, gameMode);
            al_flip_display();
            // Check if the user presses 'P' to unpause
            if (userKeyboard.keyP) {
                gameMode = GAME_ON;
                userKeyboard.keyP = false;
                buttonSetup(clickableButton, gameMode);
            }
            // Check if the user presses 'R' to restart the game
            if (userKeyboard.keyR) {
                gameMode = GAME_ON;
                buttonSetup(clickableButton, gameMode);
            }
            break;
        default:
            break;
    }
    // Checks if the user closed the display
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        continuePlaying = false;

    // Check keydown events
    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        keyDown = true;
        keyboardEvent(ev.keyboard.keycode, userKeyboard, keyDown);

    // Check key up events
    } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        keyDown = false;
        keyboardEvent(ev.keyboard.keycode, userKeyboard, keyDown);

    // Check mouse down events
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        // Check which buttons was clicked
        al_play_sample(app.buttonClick, 10.0, 0, 30.0, ALLEGRO_PLAYMODE_ONCE, 0);
        buttonClicked = true;
        checkWhichButtonAction(clickableButton, ev.mouse.x, ev.mouse.y, gameMode, buttonClicked);
        checkButtonState(clickableButton, gameMode, continuePlaying, userKeyboard, timerPaused);

    // Check mouse movement event
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
        buttonClicked = false;
        // Check if the button needs to be filled in if the mouse is hovering over it
        checkWhichButtonAction(clickableButton, ev.mouse.x, ev.mouse.y, gameMode, buttonClicked);
    }

    return  0;
}

/// This function checks to see if the objects reached the bottom of the screen to regenerate new ones
/// Need to pass the rock and power struct
/// Returns an int based on how many rocks reached the bottom
int checkIfObjectReachedBottom(Rocks rocksReachedBottom[], PowerUp powerUpReachedBottom[]) {

    // Declare variables
    int scoreIncrease = 0;

    // Check rock y-position and add score if reached bottom
    for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
        if(rocksReachedBottom[i].rockPositionY >= 800){
           rocksReachedBottom[i].rockPositionY = rand() % 500 - 500;
           rocksReachedBottom[i].rockPositionX = rand() % GENERATE_RANGE;
           scoreIncrease ++;
        }
    }

    // Check power ups y-position
    for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
        if(powerUpReachedBottom[i].powerupYCoordinate >= 800){
            setupPowerUps(powerUpReachedBottom[i]);
        }
    }

    return scoreIncrease;
}
