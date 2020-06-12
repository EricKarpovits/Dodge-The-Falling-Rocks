#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function is the main function for collision detection
/// Need to pass all the interacting structs and the number of collisions
/// Int return type
int collisionsMain(Character &mainCharacter, Rocks fallingRocks[], int &numberOfCollisions, Lives userLives[], PowerUp fallingPowerUps[]) {

    // Declare variables
    bool timerRunning;
    int returnCode;

    // Check for collision between rocks and user
    bool checkCollisionRocks = true;
    for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
        if (checkCollision(mainCharacter, fallingRocks[i], fallingPowerUps[i], checkCollisionRocks)) {
            // Check if the player is invincible
            timerRunning = al_get_timer_started(app.invincibleTimer);
            if (!timerRunning) {
                numberOfCollisions ++;
                userLives[NUMBER_OF_LIVES - numberOfCollisions].usable = false;
                al_start_timer(app.invincibleTimer);
            }
        }
    }

    // Check for collision between user and power ups
    checkCollisionRocks = false;
    for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
        if (checkCollision(mainCharacter, fallingRocks[i], fallingPowerUps[i], checkCollisionRocks)) {
            returnCode = activatePowerUp(fallingPowerUps[i], mainCharacter);
        }
    }

    // Informing the user if they are invincible
    timerRunning = al_get_timer_started(app.invincibleTimer);
    if (timerRunning) {
        al_draw_text(app.arial, RED, 310, 775, ALLEGRO_ALIGN_CENTER, "You are invincible");
    }

    // Draw a flicking collision image
    returnCode = drawInvinciblity(timerRunning, mainCharacter);
    if (returnCode != 0) {
        return returnCode;
    }

    return 0;
}

/// This function obtains the bounding box coordinates
/// Need to pass the interacting object structs
/// No return type
void obtainBoundingBoxes(Character &a, Rocks b[], PowerUp c[]) {

    // Declare variables
    int object;

    // Calculate bounding boxes
    object = CHARACTER;
    calcBoundingBoxes(a, b[0], c[0], object);

    object = ROCKS;
    for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
        calcBoundingBoxes(a, b[i], c[i], object);
    }

    object = POWER_UPS;
    for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
        calcBoundingBoxes(a, b[i], c[i], object);
    }
}

/// This function calculates the bounding box coordinates
/// Need to pass the interacting objects and a flag to know for which object to calculate the bounding boxes for
/// No return type
void calcBoundingBoxes(Character &a, Rocks &b, PowerUp &c, int object) {
    switch(object) {
        case CHARACTER:
            // Bounding box formula for calculations
            a.bbLeft = a.characterPositionX;
            a.bbTop  = a.characterPositionY;
            a.bbRight = a.bbLeft + al_get_bitmap_width(a.bitmap);
            a.bbBottom = a.bbTop + al_get_bitmap_height(a.bitmap);
            break;
        case ROCKS:
            b.bbLeft = b.rockPositionX;
            b.bbTop  = b.rockPositionY;
            b.bbRight = b.bbLeft + al_get_bitmap_width(b.bitmap);
            b.bbBottom = b.bbTop + al_get_bitmap_height(b.bitmap);
            break;
        case POWER_UPS:
            c.bbLeft = c.powerupXCoordinate;
            c.bbTop  = c.powerupYCoordinate;
            c.bbRight = c.bbLeft + al_get_bitmap_width(c.bitmap);
            c.bbBottom = c.bbTop + al_get_bitmap_height(c.bitmap);
            break;
    }
}

/// This function draws the bounding boxes in red if the user presses 'B'
/// Need to pass movable objects and the keyboard
/// No return type
void drawBoundingBox(Character &image, Rocks object[], Keyboard &userKeyboard, PowerUp powerUpImg[]) {

    if (userKeyboard.keyB) {
        al_draw_line(image.bbLeft, image.bbTop, image.bbRight, image.bbTop, RED, 1);
        al_draw_line(image.bbLeft, image.bbBottom, image.bbRight, image.bbBottom, RED, 1);
        al_draw_line(image.bbLeft, image.bbTop, image.bbLeft, image.bbBottom, RED, 1);
        al_draw_line(image.bbRight, image.bbTop, image.bbRight, image.bbBottom, RED,1);

        for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
            al_draw_line(object[i].bbLeft, object[i].bbTop, object[i].bbRight, object[i].bbTop, RED, 1);
            al_draw_line(object[i].bbLeft, object[i].bbBottom, object[i].bbRight, object[i].bbBottom, RED, 1);
            al_draw_line(object[i].bbLeft, object[i].bbTop, object[i].bbLeft, object[i].bbBottom, RED, 1);
            al_draw_line(object[i].bbRight, object[i].bbTop, object[i].bbRight, object[i].bbBottom, RED,1);
        }

        for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
            al_draw_line(powerUpImg[i].bbLeft, powerUpImg[i].bbTop, powerUpImg[i].bbRight, powerUpImg[i].bbTop, RED, 1);
            al_draw_line(powerUpImg[i].bbLeft, powerUpImg[i].bbBottom, powerUpImg[i].bbRight, powerUpImg[i].bbBottom, RED, 1);
            al_draw_line(powerUpImg[i].bbLeft, powerUpImg[i].bbTop, powerUpImg[i].bbLeft, powerUpImg[i].bbBottom, RED, 1);
            al_draw_line(powerUpImg[i].bbRight, powerUpImg[i].bbTop, powerUpImg[i].bbRight, powerUpImg[i].bbBottom, RED,1);
        }
    }
    al_flip_display();
}

/// This function checks for if collisions are occurring with the interacting objects
/// Need to pass the interacting objects and a flag to know which object collision to check for
/// Bool return type. True if there is a collision
bool checkCollision(Character &a, Rocks &b, PowerUp &c, bool checkCollisionRocks) {

    // Basically this function runs through a checklist. If it goes through the checklist without returning a false
    // Then the objects are colliding, thus returning a true.
    if (checkCollisionRocks) {
        if (a.bbBottom < b.bbTop) {
            return false;
        } else if (a.bbTop > b.bbBottom) {
            return false;
        } else if (a.bbRight < b.bbLeft) {
            return false;
        } else if (a.bbLeft > b.bbRight) {
            return false;
        }
        al_play_sample(app.collision, 1.0, 0, 10.0, ALLEGRO_PLAYMODE_ONCE, 0);
        return true;
    } else {
        if (a.bbBottom < c.bbTop) {
            return false;
        } else if (a.bbTop > c.bbBottom) {
            return false;
        } else if (a.bbRight < c.bbLeft) {
            return false;
        } else if (a.bbLeft > c.bbRight) {
            return false;
        }
        al_play_sample(app.collision, 1.0, 0, 10.0, ALLEGRO_PLAYMODE_ONCE, 0);
        return true;
    }
}

/// This function draws the character being invincible, flickering between a red and normal version of the character
/// Need to pass a bool containing if the invincible timer is running. Need to also pass the character struct
/// Int return type
int drawInvinciblity(bool &timerRunning, Character &mainCharacter){
    if (timerRunning || (!mainCharacter.drawCharacterHit && !timerRunning)) {
        if (!al_get_timer_started(app.miniTimer)) {
            if (mainCharacter.drawCharacterHit) {
                // Load the picture based on if the bool is true or false
                mainCharacter.bitmap = al_load_bitmap("mainCharacterHit.bmp");
            } else {
                mainCharacter.bitmap = al_load_bitmap("mainCharacter.bmp");
            }
        // If the user is currently mini and is invincible
        } else {
            if (mainCharacter.drawCharacterHit) {
                // Load the mini picture of the haracter
                mainCharacter.bitmap = al_load_bitmap("miniMainCharacterHit.bmp");
            } else {
                mainCharacter.bitmap = al_load_bitmap("miniMainCharacter.bmp");
            }
        }
        // Check for loading error
        if (!mainCharacter.bitmap) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_CHARACTER_IMG;
        }
        //Remove Pink Mask
        al_convert_mask_to_alpha(mainCharacter.bitmap, PINK);

        // Switch the bool so that next time this function is called it draws the opposite e.g. the character red
        mainCharacter.drawCharacterHit = !mainCharacter.drawCharacterHit;
    }
    return 0;
}
