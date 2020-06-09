#include "declarations.h"

extern ALLEGRO_FONT *arial, *smallArial;
extern ALLEGRO_TIMER *slowmoTimer, *invincibleTimer, *miniTimer, *speedIncreaser;

// This function setups the buttons coordinates based on the game mode the user is in
void buttonSetup(Button setup[], int gameMode){

    switch(gameMode){
        case START_MENU:
        case PAUSED:
            for(int i=0; i < NUMBER_OF_BUTTONS; i++){
                setButtonCoords(setup[i], SCREEN_WIDTH / 4, 150 + i*150, SCREEN_WIDTH / 4*3, 250 + i*150);
            }
            break;
        case INSTRUCTIONS:
        case CREDITS:
            for(int i=0; i < NUMBER_OF_BUTTONS - 1; i++){
                setButtonCoords(setup[i], SCREEN_WIDTH / 10 - 35 + i*200, 700, (SCREEN_WIDTH / 10 * 3.2) + i*200, 775);
            }
            break;
        case GAME_ON:
            setButtonCoords(setup[0], SCREEN_WIDTH - 90, SCREEN_HEIGHT - 30, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
    }

    for(int i=0; i<NUMBER_OF_BUTTONS; i++){
        setup[i].clicked = false;
        setup[i].filled = false;
    }
}

// This reusable function takes the coordinates from the button setup and allocates them to each specific button
void setButtonCoords(Button &button, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY) {

	button.upperLeftXCoordinate = upperLeftX;
	button.upperLeftYCoordinate = upperLeftY;
	button.lowerRightYCoordinate = lowerRightY;
	button.lowerRightXCoordinate = lowerRightX;

}

// This function draws the buttons
// The button is either drawn with just the outline or filled in based on the mouses position
void drawButtons(Button draw[], int gameMode){

    char buttonTitle[100];
    al_clear_to_color(SLATEGREY);
    switch (gameMode){
        case START_MENU:
            for(int i=0; i<NUMBER_OF_BUTTONS; i++){
                if(!draw[i].filled){
                    al_draw_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE, 3);
                } else {
                    al_draw_filled_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE);
                }
                switch (i){
                    case 0:
                        strcpy(buttonTitle, "PLAY");
                        break;
                    case 1:
                        strcpy(buttonTitle, "INSTRUCTIONS");
                        break;
                    case 2:
                        strcpy(buttonTitle, "CREDITS");
                        break;
                    case 3:
                        strcpy(buttonTitle, "QUIT");
                        break;
                }
                al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, draw[i].upperLeftYCoordinate + 37.5, ALLEGRO_ALIGN_CENTER, buttonTitle);
            }
            break;
        case INSTRUCTIONS:
        case CREDITS:
            for(int i=0; i<NUMBER_OF_BUTTONS-1; i++){
                if(!draw[i].filled){
                    al_draw_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE, 3);
                } else {
                    al_draw_filled_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE);
                }
                switch (i){
                    case 0:
                        strcpy(buttonTitle, "BACK");
                        break;
                    case 1:
                        strcpy(buttonTitle, "PLAY");
                        break;
                    case 2:
                        strcpy(buttonTitle, "QUIT");
                        break;
                }
                al_draw_text(arial, BLACK, (draw[i].upperLeftXCoordinate + draw[i].lowerRightXCoordinate) / 2, draw[i].upperLeftYCoordinate + 25, ALLEGRO_ALIGN_CENTER, buttonTitle);
            }
            break;
        case GAME_ON:
            if(!draw[0].filled){
                al_draw_rectangle(draw[0].upperLeftXCoordinate, draw[0].upperLeftYCoordinate, draw[0].lowerRightXCoordinate, draw[0].lowerRightYCoordinate, WHITE, 3);
            } else {
                al_draw_filled_rectangle(draw[0].upperLeftXCoordinate, draw[0].upperLeftYCoordinate, draw[0].lowerRightXCoordinate, draw[0].lowerRightYCoordinate, WHITE);
            }
            strcpy(buttonTitle, "PAUSE");
            al_draw_text(smallArial, BLACK, (draw[0].upperLeftXCoordinate + draw[0].lowerRightXCoordinate) / 2, draw[0].upperLeftYCoordinate + 7, ALLEGRO_ALIGN_CENTER, buttonTitle);
            break;
        case PAUSED:
            for(int i=0; i<NUMBER_OF_BUTTONS; i++){
                if(!draw[i].filled){
                    al_draw_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE, 3);
                } else {
                    al_draw_filled_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE);
                }
                switch (i){
                    case 0:
                        strcpy(buttonTitle, "UNPAUSE");
                        break;
                    case 1:
                        strcpy(buttonTitle, "RESTART");
                        break;
                    case 2:
                        strcpy(buttonTitle, "MAIN MENU");
                        break;
                    case 3:
                        strcpy(buttonTitle, "QUIT");
                        break;
                }
                al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, draw[i].upperLeftYCoordinate + 37.5, ALLEGRO_ALIGN_CENTER, buttonTitle);
            }
            break;
    }
}


void checkWhichButtonAction(Button check[], int mouseXCoordinate, int mouseYCoordinate, int gameMode, bool buttonClicked){

    for(int i=0; i < NUMBER_OF_BUTTONS; i++){
        if(mouseXCoordinate >= check[i].upperLeftXCoordinate && mouseXCoordinate <= check[i].lowerRightXCoordinate && mouseYCoordinate >= check[i].upperLeftYCoordinate && mouseYCoordinate <= check[i].lowerRightYCoordinate){
            check[i].filled = true;
            if(buttonClicked){
                check[i].clicked = true;
            }
        }else{
            check[i].filled = false;
        }
    }
}

// This function converts th
void checkButtonState(Button state[], int &gameMode, bool &continuePlaying, Keyboard &userKeyboard, Paused &timerPaused){

    int previousGameMode = gameMode;
    switch (gameMode){
        case START_MENU:
            if(state[0].clicked){
                gameMode = GAME_ON;
            } else if (state[1].clicked){
                gameMode = INSTRUCTIONS;
            } else if (state[2].clicked){
                gameMode = CREDITS;
            } else if (state[3].clicked){
                continuePlaying = false;
            }
            break;
        case INSTRUCTIONS:
        case CREDITS:
            if(state[0].clicked){
                gameMode = START_MENU;
            } else if (state[1].clicked){
                gameMode = GAME_ON;
            } else if (state[2].clicked){
                continuePlaying = false;
            }
            break;
        case GAME_ON:
            if(state[0].clicked){
                gameMode = PAUSED;
                pauseTimers(timerPaused);
            }
            break;
        case PAUSED:
            if(state[0].clicked){
                gameMode = GAME_ON;
            } else if (state[1].clicked){
                unpauseTimers(timerPaused);
                gameMode = GAME_ON;
                userKeyboard.keyR = true;
            } else if (state[2].clicked){
                gameMode = START_MENU;
                unpauseTimers(timerPaused);
                userKeyboard.keyR = true;
            } else if (state[3].clicked){
                continuePlaying = false;
            }
            break;
    }
    checkIfNewGameMode(gameMode, previousGameMode, state);
}

// This function checks if the game mode was switched in order to re setup the buttons
void checkIfNewGameMode(int newGameMode, int previousGameMode, Button b[]){

    if(newGameMode != previousGameMode){
        buttonSetup(b, newGameMode);
    }
}


