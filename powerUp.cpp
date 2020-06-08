#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *slowmoTimer, *invincibleTimer, *miniTimer, *speedIncreaser;
extern Paused timerPaused;

int activatePowerUp(PowerUp &userPowerUps, Character &userCharacter){
    if(userPowerUps.powerUpInvincibility){
        al_stop_timer(invincibleTimer);
        al_set_timer_count(invincibleTimer, 0);
        al_start_timer(invincibleTimer);
    } else if(userPowerUps.powerUpMini){
        al_stop_timer(miniTimer);
        al_set_timer_count(miniTimer, 0);
        al_start_timer(miniTimer);
        userCharacter.bitmap = al_load_bitmap("miniMainCharacter.bmp");
        al_convert_mask_to_alpha(userCharacter.bitmap, PINK);
        if (!userCharacter.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -5;
        }
    } else if(userPowerUps.powerUpSlowmo){
        al_stop_timer(slowmoTimer);
        al_set_timer_count(slowmoTimer, 0);
        al_start_timer(slowmoTimer);
    }
    setupPowerUps(userPowerUps);
}

// This is not in the main game setup because these power ups are an addon and are different objects compared to the rest of the objects
int setupPowerUps(PowerUp &powerUpSetup){

    int powerUpType;

    powerUpSetup.collision = false;

    powerUpSetup.powerUpInvincibility = false;
    powerUpSetup.powerUpMini = false;
    powerUpSetup.powerUpSlowmo = false;

    if(al_get_timer_count(speedIncreaser) < 1){
        powerUpType = rand() % 2 + 1;
    }else{
        powerUpType = rand() % 3 + 1;
    }
    switch (powerUpType){
        case 1:
            powerUpSetup.powerUpMini = true;
            break;
        case 2:
            powerUpSetup.powerUpInvincibility = true;
            break;
        case 3:
            powerUpSetup.powerUpSlowmo = true;
            break;
        default:
            printf("Error randomizing power up type");
            return -100;
            break;
    }

     powerUpSetup.powerupXCoordinate = rand() % GENERATE_RANGE;
     powerUpSetup.powerupYCoordinate = (rand() % 5000) - 5000;

    // Create a bitmap of rock and load the picture based on the specific powerUp

    if(powerUpSetup.powerUpInvincibility) {
        powerUpSetup.bitmap = al_load_bitmap("powerUpInvincibility.bmp");
    } else if (powerUpSetup.powerUpMini) {
        powerUpSetup.bitmap = al_load_bitmap("powerUpMini.bmp");
    } else if (powerUpSetup.powerUpSlowmo) {
        powerUpSetup.bitmap = al_load_bitmap("powerUpSlowmo.bmp");
    }
    if (!powerUpSetup.bitmap) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -20;
    }
    //Remove Pink Mask
    al_convert_mask_to_alpha(powerUpSetup.bitmap, PINK);

    powerUpSetup.PowerUpTimer = al_create_timer(5.0);
        if (!powerUpSetup.PowerUpTimer) {
            al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -4;
        }

    return 0;
}

int checkIfPowerUpOver(Character &userCharacter){
    // Check invincible timer
    if (al_get_timer_count(invincibleTimer) > 0){
        al_stop_timer(invincibleTimer);
        al_set_timer_count(invincibleTimer, 0);
    }
    // Check slowmo timer
    if (al_get_timer_count(slowmoTimer) > 0){
        al_stop_timer(slowmoTimer);
        al_set_timer_count(slowmoTimer, 0);
    }
    // Check mini timer
    if (al_get_timer_count(miniTimer) > 0){
        al_stop_timer(miniTimer);
        al_set_timer_count(miniTimer, 0);
        userCharacter.bitmap = al_load_bitmap("mainCharacter.bmp");
        al_convert_mask_to_alpha(userCharacter.bitmap, PINK);
        if (!userCharacter.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -5;
        }
    }
    return 0;
}

void pauseTimers(){
    timerPaused.speedIncreaser = al_get_timer_started(speedIncreaser);
    timerPaused.invincibleTimer = al_get_timer_started(invincibleTimer);
    timerPaused.miniTimer = al_get_timer_started(miniTimer);
    timerPaused.slowmoTimer = al_get_timer_started(slowmoTimer);

    if(timerPaused.speedIncreaser){
        al_stop_timer(speedIncreaser);
    }
    if(timerPaused.invincibleTimer){
        al_stop_timer(invincibleTimer);
    }
    if(timerPaused.miniTimer){
        al_stop_timer(miniTimer);
    }
    if(timerPaused.slowmoTimer){
        al_stop_timer(slowmoTimer);
    };
}

void unpauseTimers(){
    if(timerPaused.speedIncreaser){
        al_resume_timer(speedIncreaser);
    }
    if(timerPaused.invincibleTimer){
        al_resume_timer(invincibleTimer);
    }
    if(timerPaused.miniTimer){
        al_resume_timer(miniTimer);
    }
    if(timerPaused.slowmoTimer){
        al_resume_timer(slowmoTimer);
    }

    timerPaused.invincibleTimer = false;
    timerPaused.miniTimer = false;
    timerPaused.slowmoTimer = false;
    timerPaused.speedIncreaser = false;
}

