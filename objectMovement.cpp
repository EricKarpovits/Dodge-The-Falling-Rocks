#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function allows the bitmaps to move
/// Need to pass the movable object and keyboard structs
/// No return
void spriteMovement(Character &cMovement, Keyboard &kMovement, Rocks rMovement[], PowerUp pMovement[]) {

    // Take the dx and dy values and add them to the characters coordinates
    if (cMovement.characterPositionX >= 0 && cMovement.characterPositionX <= 570) {
        cMovement.characterPositionX += kMovement.xCoordinateMovement;
    } else if(cMovement.characterPositionX <= 0 && kMovement.xCoordinateMovement >= 1) {
        cMovement.characterPositionX += kMovement.xCoordinateMovement;
    } else if (cMovement.characterPositionX >= 570 && kMovement.xCoordinateMovement <= -1) {
        cMovement.characterPositionX += kMovement.xCoordinateMovement;
    }

    if (cMovement.characterPositionY >= 0 && cMovement.characterPositionY <= 705) {
        cMovement.characterPositionY += kMovement.yCoordinateMovement;
    } else if(cMovement.characterPositionY <= 0 && kMovement.yCoordinateMovement >= 1) {
        cMovement.characterPositionY += kMovement.yCoordinateMovement;
    } else if (cMovement.characterPositionY >= 705 && kMovement.yCoordinateMovement <= -1) {
        cMovement.characterPositionY += kMovement.yCoordinateMovement;
    }

    // Movement of the rocks and power ups based on if the slow motion power up is enabled
    if (!al_get_timer_started(app.slowmoTimer)) {
        for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
            rMovement[i].rockPositionY += 1 + al_get_timer_count(app.speedIncreaser);
        }

        for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
            pMovement[i].powerupYCoordinate += 2 * (1 + al_get_timer_count(app.speedIncreaser));
        }
    } else {
        for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
            rMovement[i].rockPositionY += 1;
        }

        for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
            pMovement[i].powerupYCoordinate += 2;
        }
    }
}

/// This function translates the keyboard booleans to a dx and dy which will move the character
/// Need to pass the keyboard struct
/// No return type
void keyboardMovement(Keyboard &movement) {

    // Vertical movement
    if (movement.keyDown && movement.keyUp){
        movement.yCoordinateMovement = 0;
    } else if (movement.keyUp) {
        movement.yCoordinateMovement = -1 - al_get_timer_count(app.speedIncreaser);
    } else if (movement.keyDown) {
        movement.yCoordinateMovement = 1 + al_get_timer_count(app.speedIncreaser);
    } else {
        movement.yCoordinateMovement = 0;
    }

    // Horizontal movement
    if (movement.keyRight && movement.keyLeft){
        movement.xCoordinateMovement = 0;
    } else if (movement.keyLeft) {
        movement.xCoordinateMovement = -1 - al_get_timer_count(app.speedIncreaser);
    } else if (movement.keyRight) {
        movement.xCoordinateMovement = 1 + al_get_timer_count(app.speedIncreaser);
    } else {
        movement.xCoordinateMovement = 0;
    }

    // Double speed
    if (movement.keySpace) {
        movement.xCoordinateMovement *= 2;
        movement.yCoordinateMovement *= 2;
    }
}

/// This function makes the bool turn true or false based of if the key is pressed or released
/// Essentially translating the key codes to a bool
/// Need to pass the key code the keyboard struct and flag if it was a key down or key up event allowing the function to be reused
/// For multiple events
/// No return type
void keyboardEvent(int keycode, Keyboard &event, bool keyDown) {

    // Key code to bool translation
    switch(keycode) {
        case ALLEGRO_KEY_UP:
            event.keyUp = !event.keyUp;
            break;
        case ALLEGRO_KEY_DOWN:
            event.keyDown = !event.keyDown;
            break;
        case ALLEGRO_KEY_LEFT:
            event.keyLeft = !event.keyLeft;
            break;
        case ALLEGRO_KEY_RIGHT:
            event.keyRight = !event.keyRight;
            break;
        case ALLEGRO_KEY_SPACE:
            event.keySpace = !event.keySpace;
            break;
        case ALLEGRO_KEY_R:
            // Only allows the key to become true when key down
            if (keyDown) {
               event.keyR = true;
            }
            break;
        case ALLEGRO_KEY_P:
            // Only allows the bool to change value when it is key down
            if (keyDown && !event.keyP) {
                event.keyP = true;
            } else if (keyDown && event.keyP) {
                event.keyP = false;
            }
            break;
        case ALLEGRO_KEY_B:
            if (keyDown && !event.keyB) {
                event.keyB = true;
            } else if (keyDown && event.keyB) {
                event.keyB = false;
            }
            break;
        default:
            break;
    }
}

/// The function takes the objects x and y coordinates and draws the image at those coordinates when the timer event occurs
/// Need to pass the movable object structs
/// No return type
void drawSprites(Character &cDraw, Rocks rDraw[], Lives lDraw[], PowerUp pDraw[]) {

    // Draw all the objects in the game
    al_draw_bitmap(cDraw.bitmap, cDraw.characterPositionX, cDraw.characterPositionY, 0);

    for (int i=0; i<NUMBER_OF_LIVES; i++) {
        if (lDraw[i].usable) {
            al_draw_bitmap(lDraw[i].bitmap, lDraw[i].xCoordinate, lDraw[i].yCoordinate, 0);
        }
    }

    for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
        al_draw_bitmap(rDraw[i].bitmap, rDraw[i].rockPositionX, rDraw[i].rockPositionY, 0);
    }

    for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
        al_draw_bitmap(pDraw[i].bitmap, pDraw[i].powerupXCoordinate, pDraw[i].powerupYCoordinate, 0);
    }
}

/// This function prints out the level the user is on, on the bottom left corner
/// No return type
void userLevel() {

    // Declare variables
    int obtainUserLevel = 0;

    // Obtain timer count and add one as the count starts at 0
    obtainUserLevel = al_get_timer_count(app.speedIncreaser) + 1;
    al_draw_textf(app.arial, RED, 0, 775, ALLEGRO_ALIGN_LEFT, "Level %d", obtainUserLevel);
}

