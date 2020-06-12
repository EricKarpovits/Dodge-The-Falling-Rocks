#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function either activates the timers or resets the timer back to 0 if the user obtains the same power up
/// before the power up is over
/// Need to pass the power up and character struct
/// Returns an int
int activatePowerUp(PowerUp &userPowerUps, Character &userCharacter) {

    if (userPowerUps.powerUpInvincibility) {
        // When you start a timer that was stopped, it automatically starts the timer from 0
        al_stop_timer(app.invincibleTimer);
        al_set_timer_count(app.invincibleTimer, 0);
        al_start_timer(app.invincibleTimer);

    } else if (userPowerUps.powerUpMini) {
        al_stop_timer(app.miniTimer);
        al_set_timer_count(app.miniTimer, 0);
        al_start_timer(app.miniTimer);
        // Make the user turn small
        userCharacter.bitmap = al_load_bitmap("miniMainCharacter.bmp");
        al_convert_mask_to_alpha(userCharacter.bitmap, PINK);
        // Check for loading erros
        if (!userCharacter.bitmap) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to mini character image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_MINI_CHARACTER_IMG;
        }

    // Start or reset the slow motion power up
    } else if (userPowerUps.powerUpSlowmo) {
        al_stop_timer(app.slowmoTimer);
        al_set_timer_count(app.slowmoTimer, 0);
        al_start_timer(app.slowmoTimer);
    }

    // Set a new power up if the user collided with one
    setupPowerUps(userPowerUps);

    return 0;
}

/// Set ups the power ups at the start and throughout the game
/// Need to pass the power up struct
/// Returns an int (0) if no errors
int setupPowerUps(PowerUp &powerUpSetup) {

    // Declare variables
    int powerUpType;

    // Initializing the power up bool
    powerUpSetup.collision = false;
    powerUpSetup.powerUpInvincibility = false;
    powerUpSetup.powerUpMini = false;
    powerUpSetup.powerUpSlowmo = false;

    // Generates a random number to chose a timer
    // NOTE: If the user is on level 1 a slow motion power up will not generate
    if (al_get_timer_count(app.speedIncreaser) < 1) {
        powerUpType = rand() % 2 + 1;
    } else {
        powerUpType = rand() % 3 + 1;
    }

    // Convert the rnd int to activate the power up
    switch (powerUpType) {
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
    if(powerUpSetup.powerUpInvincibility) {
        powerUpSetup.bitmap = al_load_bitmap("powerUpInvincibility.bmp");
    }else if (powerUpSetup.powerUpMini){
        powerUpSetup.bitmap = al_load_bitmap("powerUpMini.bmp");
    }else if (powerUpSetup.powerUpSlowmo){
        powerUpSetup.bitmap = al_load_bitmap("powerUpSlowmo.bmp");
    }
    if (!powerUpSetup.bitmap) {
        al_show_native_message_box(app.display, "Error", "Error", "Failed to load power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(app.display);
        return ERROR_POWERUP_IMG;
    }

    //Remove Pink Mask
    al_convert_mask_to_alpha(powerUpSetup.bitmap, PINK);

    return 0;
}

/// This function checks if the power ups are over based on their timer
/// Need to pass the character struct to reset the image if the character was small
/// Return an int
int checkIfPowerUpOver(Character &userCharacter){

    // Check invincible timer
    if (al_get_timer_count(app.invincibleTimer) > 0) {
        al_stop_timer(app.invincibleTimer);
        al_set_timer_count(app.invincibleTimer, 0);
    }
    // Check slowmo timer
    if (al_get_timer_count(app.slowmoTimer) > 0) {
        al_stop_timer(app.slowmoTimer);
        al_set_timer_count(app.slowmoTimer, 0);
    }
    // Check mini timer & load back the regular image
    if (al_get_timer_count(app.miniTimer) > 0) {
        al_stop_timer(app.miniTimer);
        al_set_timer_count(app.miniTimer, 0);

        userCharacter.bitmap = al_load_bitmap("mainCharacter.bmp");
        al_convert_mask_to_alpha(userCharacter.bitmap, PINK);
        // Check for loading erros
        if (!userCharacter.bitmap) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load character image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_CHARACTER_IMG;
        }
    }

    return 0;
}


