#include "declarations.h"

extern ALLEGRO_FONT *arial;
extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *invincibleTimer, *miniTimer;

int collisionsMain(Character &mainCharacter, Rocks fallingRocks[], int &numberOfCollisions, Lives userLives[], PowerUp fallingPowerUps[]){
    bool timerRunning;
    int returnCode;

    // Check for collision with rocks and user
    bool checkCollisionRocks = true;
    for(int i = 0; i < NUMBER_OF_ROCKS; i++){
        if (checkCollision(mainCharacter, fallingRocks[i], fallingPowerUps[i], checkCollisionRocks)){
            timerRunning = al_get_timer_started(invincibleTimer);
            if (!timerRunning){
                numberOfCollisions ++;
                printf("%d\n", numberOfCollisions);
                userLives[NUMBER_OF_LIVES - numberOfCollisions].usable = false;
                al_start_timer(invincibleTimer);
            }
        }
    }
    checkCollisionRocks = false;
    for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
        if (checkCollision(mainCharacter, fallingRocks[i], fallingPowerUps[i], checkCollisionRocks)){
            returnCode = activatePowerUp(fallingPowerUps[i], mainCharacter);
        }
    }

    timerRunning = al_get_timer_started(invincibleTimer);
    if(timerRunning){
        al_draw_text(arial, RED, 310, 775, ALLEGRO_ALIGN_CENTER, "You are invincible");
    }

    // Draw a flicking collision image
    returnCode = drawCollision(timerRunning, mainCharacter);
    if (returnCode != 0) {
        printf("Returning error code %d.", returnCode);
        return returnCode;
    }
    return 0;
}

// This function calculates where the bounding boxes are
void calcBoundsDrawing(Character &a, Rocks b[], PowerUp c[]){
    a.bbLeft = a.characterPositionX;
	a.bbTop  = a.characterPositionY;
	a.bbRight = a.bbLeft + al_get_bitmap_width(a.bitmap);
	a.bbBottom = a.bbTop + al_get_bitmap_height(a.bitmap);

    for(int i = 0; i < NUMBER_OF_ROCKS; i++){
        b[i].bbLeft = b[i].rockPositionX;
        b[i].bbTop  = b[i].rockPositionY;
        b[i].bbRight = b[i].bbLeft + al_get_bitmap_width(b[i].bitmap);
        b[i].bbBottom = b[i].bbTop + al_get_bitmap_height(b[i].bitmap);
    }

    for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
        c[i].bbLeft = c[i].powerupXCoordinate;
        c[i].bbTop  = c[i].powerupYCoordinate;
        c[i].bbRight = c[i].bbLeft + al_get_bitmap_width(c[i].bitmap);
        c[i].bbBottom = c[i].bbTop + al_get_bitmap_height(c[i].bitmap);
    }

}

// This function draws the bounding boxes in red if the user presses b
void drawBoundingBox(Character &image, Rocks object[], Keyboard &userKeyboard, PowerUp powerUpImg[]){
    if(userKeyboard.keyB){
        al_draw_line(image.bbLeft, image.bbTop, image.bbRight, image.bbTop, RED, 1);
        al_draw_line(image.bbLeft, image.bbBottom, image.bbRight, image.bbBottom, RED, 1);
        al_draw_line(image.bbLeft, image.bbTop, image.bbLeft, image.bbBottom, RED, 1);
        al_draw_line(image.bbRight, image.bbTop, image.bbRight, image.bbBottom, RED,1);

        for(int i = 0; i < NUMBER_OF_ROCKS; i++){
            al_draw_line(object[i].bbLeft, object[i].bbTop, object[i].bbRight, object[i].bbTop, RED, 1);
            al_draw_line(object[i].bbLeft, object[i].bbBottom, object[i].bbRight, object[i].bbBottom, RED, 1);
            al_draw_line(object[i].bbLeft, object[i].bbTop, object[i].bbLeft, object[i].bbBottom, RED, 1);
            al_draw_line(object[i].bbRight, object[i].bbTop, object[i].bbRight, object[i].bbBottom, RED,1);
        }
        for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
            al_draw_line(powerUpImg[i].bbLeft, powerUpImg[i].bbTop, powerUpImg[i].bbRight, powerUpImg[i].bbTop, RED, 1);
            al_draw_line(powerUpImg[i].bbLeft, powerUpImg[i].bbBottom, powerUpImg[i].bbRight, powerUpImg[i].bbBottom, RED, 1);
            al_draw_line(powerUpImg[i].bbLeft, powerUpImg[i].bbTop, powerUpImg[i].bbLeft, powerUpImg[i].bbBottom, RED, 1);
            al_draw_line(powerUpImg[i].bbRight, powerUpImg[i].bbTop, powerUpImg[i].bbRight, powerUpImg[i].bbBottom, RED,1);
        }
    }
    al_flip_display();
}

// This function checks for if collisions are occurring with the rocks
bool checkCollision(Character &a, Rocks &b, PowerUp &c, bool checkCollisionRocks){
    //  printf("Character: %d, %d, %d, %d\n", a.bbBottom, a.bbLeft, a.bbRight, a.bbTop);
    //printf("Rock: %d, %d, %d, %d\n", b.bbBottom, b.bbLeft, b.bbRight, b.bbTop);

    if (checkCollisionRocks){
        if (a.bbBottom < b.bbTop) {
            return false;
        }else if (a.bbTop > b.bbBottom) {
            return false;
        }else if (a.bbRight < b.bbLeft) {
            return false;
        }else if (a.bbLeft > b.bbRight) {
            return false;
        }return true;
    } else {
        if (a.bbBottom < c.bbTop) {
            return false;
        }else if (a.bbTop > c.bbBottom) {
            return false;
        }else if (a.bbRight < c.bbLeft) {
            return false;
        }else if (a.bbLeft > c.bbRight) {
            return false;
        }return true;
    }
}

int drawCollision(bool &timerRunning, Character &mainCharacter){
    if(timerRunning || (!mainCharacter.drawCharacterHit && !timerRunning)){
        if(!al_get_timer_started(miniTimer)){
            if(mainCharacter.drawCharacterHit){
                // Create a bitmap character and load the picture
                mainCharacter.bitmap = al_load_bitmap("mainCharacterHit.bmp");
            } else {
                mainCharacter.bitmap = al_load_bitmap("mainCharacter.bmp");
            }
        } else {
            if(mainCharacter.drawCharacterHit){
                // Create a mini bitmap of the character and load the picture
                mainCharacter.bitmap = al_load_bitmap("miniMainCharacterHit.bmp");
            } else {
                mainCharacter.bitmap = al_load_bitmap("miniMainCharacter.bmp");
            }
        }
        if (!mainCharacter.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -5;
        }
        //Remove Pink Mask
        al_convert_mask_to_alpha(mainCharacter.bitmap, PINK);

        mainCharacter.drawCharacterHit = !mainCharacter.drawCharacterHit;
    }
    return 0;
}
