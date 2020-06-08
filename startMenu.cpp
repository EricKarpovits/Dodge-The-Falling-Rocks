#include "declarations.h"

extern ALLEGRO_FONT *arial, *smallArial;
extern ALLEGRO_TIMER *slowmoTimer, *invincibleTimer, *miniTimer, *speedIncreaser;


void buttonSetup(Button setup[], int gameMode){

    switch(gameMode){
        case 1:
        case 6:
            for(int i=0; i < NUMBER_OF_BUTTONS; i++){
                setup[i].upperLeftXCoordinate = SCREEN_WIDTH / 4;
                setup[i].upperLeftYCoordinate = 150 + i*150;
                setup[i].lowerRightYCoordinate = 250 + i*150;
                setup[i].lowerRightXCoordinate = SCREEN_WIDTH / 4 * 3;
            }
            break;
        case 2:
        case 4:
            for(int i=0; i < NUMBER_OF_BUTTONS - 1; i++){
                setup[i].upperLeftXCoordinate = SCREEN_WIDTH / 10 - 35 + 200*i;
                setup[i].upperLeftYCoordinate = 700;
                setup[i].lowerRightYCoordinate = 775;
                setup[i].lowerRightXCoordinate = (SCREEN_WIDTH / 10 * 3.2) + 200*i;
            }
            break;
        case 3:
            setup[0].upperLeftXCoordinate = SCREEN_WIDTH - 90;
            setup[0].upperLeftYCoordinate = SCREEN_HEIGHT - 30;
            setup[0].lowerRightYCoordinate = SCREEN_HEIGHT;
            setup[0].lowerRightXCoordinate = SCREEN_WIDTH;

            break;
    }
    for(int i=0; i<NUMBER_OF_BUTTONS; i++){
        setup[i].clicked = false;
        setup[i].filled = false;
    }
}
void drawButtons(Button draw[], int gameMode){

    char buttonTitle[100];
    al_clear_to_color(SLATEGREY);
    switch (gameMode){
        case 1:
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
        case 2:
        case 4:
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
        case 3:
            if(!draw[0].filled){
                al_draw_rectangle(draw[0].upperLeftXCoordinate, draw[0].upperLeftYCoordinate, draw[0].lowerRightXCoordinate, draw[0].lowerRightYCoordinate, WHITE, 3);
            } else {
                al_draw_filled_rectangle(draw[0].upperLeftXCoordinate, draw[0].upperLeftYCoordinate, draw[0].lowerRightXCoordinate, draw[0].lowerRightYCoordinate, WHITE);
            }
            strcpy(buttonTitle, "PAUSE");
            al_draw_text(smallArial, BLACK, (draw[0].upperLeftXCoordinate + draw[0].lowerRightXCoordinate) / 2, draw[0].upperLeftYCoordinate + 7, ALLEGRO_ALIGN_CENTER, buttonTitle);
            break;
        case 6:
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

void checkWhichButtonClicked(Button check[], int mouseXCoordinate, int mouseYCoordinate, int gameMode){
    for(int i=0; i < NUMBER_OF_BUTTONS; i++){
        if(mouseXCoordinate >= check[i].upperLeftXCoordinate && mouseXCoordinate <= check[i].lowerRightXCoordinate && mouseYCoordinate >= check[i].upperLeftYCoordinate && mouseYCoordinate <= check[i].lowerRightYCoordinate){
            check[i].clicked = true;
        }
    }
}
void checkButtonState(Button state[], int &gameMode, bool &continuePlaying, bool &closedDisplay, Keyboard &userKeyboard){
    int previousGameMode = gameMode;
    switch (gameMode){
        case 1:
            if(state[0].clicked){
                gameMode = 3;
            } else if (state[1].clicked){
                gameMode = 2;
            } else if (state[2].clicked){
                gameMode = 4;
            } else if (state[3].clicked){
                continuePlaying = false;
                closedDisplay = true;
            }
            break;
        case 2:
        case 4:
            if(state[0].clicked){
                gameMode = 1;
            } else if (state[1].clicked){
                gameMode = 3;
            } else if (state[2].clicked){
                continuePlaying = false;
                closedDisplay = true;
            }
            break;
        case 3:
            if(state[0].clicked){
                gameMode = 6;
                pauseTimers();
            }
            break;
        case 6:
            if(state[0].clicked){
                gameMode = 3;
            } else if (state[1].clicked){
                unpauseTimers();
                gameMode = 3;
                userKeyboard.keyR = true;
            } else if (state[2].clicked){
                gameMode = 1;
                unpauseTimers();
                userKeyboard.keyR = true;
            } else if (state[3].clicked){
                continuePlaying = false;
                closedDisplay = true;
            }
            break;
    }
    checkIfNewGameMode(gameMode, previousGameMode, state);
}

void checkIfNewGameMode(int newGameMode, int previousGameMode, Button b[]){
    if(newGameMode != previousGameMode){
        buttonSetup(b, newGameMode);
    }
}

void detectButtonHover(Button hover[], int mouseXCoordinate, int mouseYCoordinate, int gameMode){
    for(int i=0; i < NUMBER_OF_BUTTONS; i++){
        if(mouseXCoordinate >= hover[i].upperLeftXCoordinate && mouseXCoordinate <= hover[i].lowerRightXCoordinate && mouseYCoordinate >= hover[i].upperLeftYCoordinate && mouseYCoordinate <= hover[i].lowerRightYCoordinate){
            hover[i].filled = true;
        } else {
            hover[i].filled = false;
        }
    }
}


