#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *slowmoTimer, *invincibleTimer, *miniTimer, *speedIncreaser;

// This function either activates the timers or resets the timer back to 0
// if the user gets two consecutive power ups before the power up is over
int activatePowerUp(PowerUp &userPowerUps, Character &userCharacter){

    if(userPowerUps.powerUpInvincibility){
        // When you start a timer that was stopped, it automatically starts the timer from 0
        al_stop_timer(invincibleTimer);
        al_start_timer(invincibleTimer);
    } else if(userPowerUps.powerUpMini){
        al_stop_timer(miniTimer);
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
        al_start_timer(slowmoTimer);
    }

    setupPowerUps(userPowerUps);

    return 0;
}

// This is not in the main game setup because these power ups are an addon and are different objects compared to the rest of the objects
int setupPowerUps(PowerUp &powerUpSetup){

    // Declare variables
    int powerUpType;

    // Initializing the power up bool
    powerUpSetup.collision = false;
    powerUpSetup.powerUpInvincibility = false;
    powerUpSetup.powerUpMini = false;
    powerUpSetup.powerUpSlowmo = false;

    // Generates a random number to chose a timer
    // NOTE: If the user is on level 1 a slow motion power up will not generate
    if(al_get_timer_count(speedIncreaser) < 1){
        powerUpType = rand() % 2 + 1;
    }else{
        powerUpType = rand() % 3 + 1;
    }

    // Convert the rnd int to activate the power up
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
    }

    // Generate spawn location
    powerUpSetup.powerupXCoordinate = rand() % GENERATE_RANGE;
    powerUpSetup.powerupYCoordinate = (rand() % 5000) - 5000;

    // Load the image for the appropriate power up
    if(powerUpSetup.powerUpInvincibility){
        powerUpSetup.bitmap = al_load_bitmap("powerUpInvincibility.bmp");
    }else if (powerUpSetup.powerUpMini){
        powerUpSetup.bitmap = al_load_bitmap("powerUpMini.bmp");
    }else if (powerUpSetup.powerUpSlowmo){
        powerUpSetup.bitmap = al_load_bitmap("powerUpSlowmo.bmp");
    }
    if (!powerUpSetup.bitmap) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -20;
    }

    //Remove Pink Mask
    al_convert_mask_to_alpha(powerUpSetup.bitmap, PINK);

    return 0;
}

// This function checks if the power ups are over based on their timer
int checkIfPowerUpOver(Character &userCharacter){

    // Check invincible timer
    if (al_get_timer_count(invincibleTimer) > 0){
        al_stop_timer(invincibleTimer);
    }
    // Check slowmo timer
    if (al_get_timer_count(slowmoTimer) > 0){
        al_stop_timer(slowmoTimer);
    }
    // Check mini timer & load back the regular image
    if (al_get_timer_count(miniTimer) > 0){
        al_stop_timer(miniTimer);
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

//This function pauses the timer once the user pauses the game
void pauseTimers(Paused &timerPaused){

    // Check if the timer is running
    timerPaused.speedIncreaser = al_get_timer_started(speedIncreaser);
    timerPaused.invincibleTimer = al_get_timer_started(invincibleTimer);
    timerPaused.miniTimer = al_get_timer_started(miniTimer);
    timerPaused.slowmoTimer = al_get_timer_started(slowmoTimer);

    // If the timer is running then pause the timer based on the bool
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
    }
}

// This function unpauses the timers once the user unpauses the game
void unpauseTimers(Paused &timerPaused){

    // Based on if the timer was paused the timer will now resume
    if(timerPaused.speedIncreaser){
        al_resume_timer(speedIncreaser);
        timerPaused.speedIncreaser = false;
    }
    if(timerPaused.invincibleTimer){
        al_resume_timer(invincibleTimer);
        timerPaused.invincibleTimer = false;
    }
    if(timerPaused.miniTimer){
        al_resume_timer(miniTimer);
        timerPaused.miniTimer = false;
    }
    if(timerPaused.slowmoTimer){
        al_resume_timer(slowmoTimer);
        timerPaused.slowmoTimer = false;
    }
}

