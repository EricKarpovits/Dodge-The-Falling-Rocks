#include "declarations.h"

extern ALLEGRO_TIMER *speedIncreaser, *slowmoTimer;
extern ALLEGRO_FONT *arial;

// This function allows the bitmaps to move
void spriteMovement(Character &cMovement, Keyboard &kMovement, Rocks rMovement[], PowerUp pMovement[]){

    if(cMovement.characterPositionX >= 0 && cMovement.characterPositionX <= 570){
        cMovement.characterPositionX += kMovement.xCoordinateMovement;
    } else if(cMovement.characterPositionX <= 0 && kMovement.xCoordinateMovement >= 1) {
        cMovement.characterPositionX += kMovement.xCoordinateMovement;
    } else if (cMovement.characterPositionX >= 570 && kMovement.xCoordinateMovement <= -1){
        cMovement.characterPositionX += kMovement.xCoordinateMovement;
    }

    if(cMovement.characterPositionY >= 0 && cMovement.characterPositionY <= 705){
        cMovement.characterPositionY += kMovement.yCoordinateMovement;
    } else if(cMovement.characterPositionY <= 0 && kMovement.yCoordinateMovement >= 1) {
        cMovement.characterPositionY += kMovement.yCoordinateMovement;
    } else if (cMovement.characterPositionY >= 705 && kMovement.yCoordinateMovement <= -1){
        cMovement.characterPositionY += kMovement.yCoordinateMovement;
    }
    if(!al_get_timer_started(slowmoTimer)){
        for(int i = 0; i < NUMBER_OF_ROCKS; i++){
            rMovement[i].rockPositionY += 1 + al_get_timer_count(speedIncreaser);
        }

        for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
            pMovement[i].powerupYCoordinate += 2 * (1 + al_get_timer_count(speedIncreaser));
        }
    } else {
        for(int i = 0; i < NUMBER_OF_ROCKS; i++){
            rMovement[i].rockPositionY += 1;
        }

        for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
            pMovement[i].powerupYCoordinate += 2;
        }
    }
}

// This movement translates the booleans to a movement
void keyboardMovement(Keyboard &movement){
    if (movement.keyDown && movement.keyUp){
        movement.yCoordinateMovement = 0;
    }else if (movement.keyUp){
        movement.yCoordinateMovement = -1 - al_get_timer_count(speedIncreaser);
    }else if (movement.keyDown){
        movement.yCoordinateMovement = 1 + al_get_timer_count(speedIncreaser);
    }else{
        movement.yCoordinateMovement = 0;
    }

    if (movement.keyRight && movement.keyLeft){
        movement.xCoordinateMovement = 0;
    }else if (movement.keyLeft){
        movement.xCoordinateMovement = -1 - al_get_timer_count(speedIncreaser);
    }else if (movement.keyRight){
        movement.xCoordinateMovement = 1 + al_get_timer_count(speedIncreaser);
    }else{
        movement.xCoordinateMovement = 0;
    }

    if (movement.keySpace){
        movement.xCoordinateMovement *= 2;
        movement.yCoordinateMovement *= 2;
    }
}

// This function makes the bool turn true when the key is pressed
void eventKeyDown(int keycode, Keyboard &event){
    switch(keycode) {
        case ALLEGRO_KEY_UP:
            event.keyUp = true;
            break;
        case ALLEGRO_KEY_DOWN:
            event.keyDown = true;
            break;
        case ALLEGRO_KEY_LEFT:
            event.keyLeft = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            event.keyRight = true;
            break;
        case ALLEGRO_KEY_SPACE:
            event.keySpace = !event.keySpace;
            break;
        case ALLEGRO_KEY_B:
            event.keyB = !event.keyB;
            break;
        case ALLEGRO_KEY_R:
            event.keyR = true;
            break;
        case ALLEGRO_KEY_P:
            event.keyP = !event.keyP;
            break;
        default:
            break;
    }
}

// This function makes the bool turn false when the key is released
void eventKeyUp(int keycode, Keyboard &event){
    switch(keycode) {
        case ALLEGRO_KEY_UP:
            event.keyUp = false;
            break;
        case ALLEGRO_KEY_DOWN:
            event.keyDown = false;
            break;
        case ALLEGRO_KEY_LEFT:
            event.keyLeft = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            event.keyRight = false;
            break;
        case ALLEGRO_KEY_SPACE:
            event.keySpace = !event.keySpace;
            break;
        default:
            break;
    }
}

// This function draws the images of the sprites every time the timer tells it too
void drawSprites(Character &cDraw, Rocks rDraw[], Lives lDraw[], PowerUp pDraw[]){

    // The function takes the objects x and y coordinates and draws the image at those coordinates

    al_draw_bitmap(cDraw.bitmap, cDraw.characterPositionX, cDraw.characterPositionY, 0);

    for(int i=0; i<NUMBER_OF_LIVES; i++){
        if(lDraw[i].usable){
            al_draw_bitmap(lDraw[i].bitmap, lDraw[i].xCoordinate, lDraw[i].yCoordinate, 0);
        }
    }

    for (int i = 0; i < NUMBER_OF_ROCKS; i++){
        al_draw_bitmap(rDraw[i].bitmap, rDraw[i].rockPositionX, rDraw[i].rockPositionY, 0);
    }

    for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
        al_draw_bitmap(pDraw[i].bitmap, pDraw[i].powerupXCoordinate, pDraw[i].powerupYCoordinate, 0);
    }
}


void userLevel(){
    int obtainUserLevel = al_get_timer_count(speedIncreaser) + 1;
    al_draw_textf(arial, RED, 0, 775, ALLEGRO_ALIGN_LEFT, "Level %d", obtainUserLevel);
}

