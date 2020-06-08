#include "declarations.h"

extern ALLEGRO_TIMER *slowmoTimer, *invincibleTimer, *miniTimer, *speedIncreaser, *timer;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_FONT *arial;
extern Paused timerPaused;

int playGame(bool &continuePlaying, bool &closedDisplay, int &userScore, int &numberOfCollisions,  Keyboard &userKeyboard, Character &mainCharacter, Rocks fallingRocks[], Lives userLives[], PowerUp fallingPowerUps[], int &gameMode, Button clickableButton[]){

    // Declare variables and create an event
    int returnCode;
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);

    switch (gameMode) {
        case 1:
            drawButtons(clickableButton, gameMode);
            al_draw_text(arial, BLACK, 0, 773, 0, "By Eric Karpovits");
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 75, ALLEGRO_ALIGN_CENTER, "Dodge the Falling Rocks");
            al_flip_display();
            break;
        case 2:
            drawButtons(clickableButton, gameMode);
            returnCode = gameInstructions();
            if (returnCode != 0){
                printf("Returning error code %d", returnCode);
                return returnCode;
            }
            break;
        case 3:
            al_start_timer(speedIncreaser);
            // Restart the game if the user presses R
            if(userKeyboard.keyR){
                setupMain(mainCharacter, userLives, fallingRocks, userKeyboard, fallingPowerUps);
                userScore = 0;
                numberOfCollisions = 0;
            }

            if(timerPaused.invincibleTimer || timerPaused.miniTimer || timerPaused.slowmoTimer || timerPaused.speedIncreaser){
                unpauseTimers();
            }

            // Event timer
            if (ev.type == ALLEGRO_EVENT_TIMER) {

                // This is an if statement which does not allow any movement to occur
                if(userKeyboard.keyP){
                    gameMode = 6;
                    buttonSetup(clickableButton, gameMode);
                    userKeyboard.keyP = false;
                    pauseTimers();
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
                calcBoundsDrawing(mainCharacter, fallingRocks, fallingPowerUps);

                // Draw a flicking collision image
                returnCode = collisionsMain(mainCharacter, fallingRocks, numberOfCollisions, userLives, fallingPowerUps);

                if(!userLives[0].usable){
                    gameMode = 5;
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
        case 4:
            drawButtons(clickableButton, gameMode);
            credits();
            break;
        case 5:
            checkHighScore(userScore, closedDisplay);
            userKeyboard.keyR = true;
            gameMode = 1;
            buttonSetup(clickableButton, gameMode);
            break;
        case 6:
            drawButtons(clickableButton, gameMode);
            al_flip_display();
            if (userKeyboard.keyP){
                gameMode = 3;
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
        closedDisplay = true;
    }
    // Set direction if key pressed
    else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
        eventKeyDown(ev.keyboard.keycode, userKeyboard);
    // Stop movement if key is released
    } else if (ev.type == ALLEGRO_EVENT_KEY_UP){
        eventKeyUp(ev.keyboard.keycode, userKeyboard);
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        checkWhichButtonClicked(clickableButton, ev.mouse.x, ev.mouse.y, gameMode);
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES){
       printf("%d %d\n", ev.mouse.x, ev.mouse.y);
        detectButtonHover(clickableButton, ev.mouse.x, ev.mouse.y, gameMode);
    }
    checkButtonState(clickableButton, gameMode, continuePlaying, closedDisplay, userKeyboard);

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
