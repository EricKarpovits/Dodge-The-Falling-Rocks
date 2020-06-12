#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function checks if the file loaded
/// Need to pass the file
/// Int return type
int checkIfFileLoaded(FILE *fptr){

    if (!fptr) {
        al_show_native_message_box(app.display, "Error", "Error", "Failed to load text file!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(app.display);
        return ERROR_LOAD_FPTR;
    }

    return 0;
}

/// This function pauses the timers once the user pauses the game
/// Need to pass the timer paused struct
/// No return type
void pauseTimers(Paused &timerPaused) {

    // Check if the timer is running, and make the bool true for future un pausing use too
    timerPaused.speedIncreaser = al_get_timer_started(app.speedIncreaser);
    timerPaused.invincibleTimer = al_get_timer_started(app.invincibleTimer);
    timerPaused.miniTimer = al_get_timer_started(app.miniTimer);
    timerPaused.slowmoTimer = al_get_timer_started(app.slowmoTimer);

    // If the timers are running, they will now be paused
    if (timerPaused.speedIncreaser) {
        al_stop_timer(app.speedIncreaser);
    }
    if (timerPaused.invincibleTimer) {
        al_stop_timer(app.invincibleTimer);
    }
    if (timerPaused.miniTimer) {
        al_stop_timer(app.miniTimer);
    }
    if (timerPaused.slowmoTimer) {
        al_stop_timer(app.slowmoTimer);
    }
}

/// This function unpauses the timers once the user unpauses the game
/// Need to pass the timer paused struct
/// No return type
void unpauseTimers(Paused &timerPaused) {

    // If the timers were paused this function will now resume
    if (timerPaused.speedIncreaser) {
        al_resume_timer(app.speedIncreaser);
        timerPaused.speedIncreaser = false;
    }
    if (timerPaused.invincibleTimer) {
        al_resume_timer(app.invincibleTimer);
        timerPaused.invincibleTimer = false;
    }
    if (timerPaused.miniTimer) {
        al_resume_timer(app.miniTimer);
        timerPaused.miniTimer = false;
    }
    if (timerPaused.slowmoTimer) {
        al_resume_timer(app.slowmoTimer);
        timerPaused.slowmoTimer = false;
    }
}

/// This function converts which button was clicked to an the appropriate action (game mode or end the game)
/// Need to pass the button, game mode, the continue playing bool, the keyboard, and the paused timers bool struct containing the info about if a timer is paused or not
/// No return type
void checkButtonState(Button state[], int &gameMode, bool &continuePlaying, Keyboard &userKeyboard, Paused &timerPaused) {

    // Declare variables
    int previousGameMode = gameMode;

    // Switch game mode
    switch (gameMode) {
        case START_MENU:
            // Based on which button was clicked the appropriate action is performed
            if (state[0].clicked) {
                gameMode = GAME_ON;
            } else if (state[1].clicked) {
                gameMode = INSTRUCTIONS;
            } else if (state[2].clicked) {
                gameMode = CREDITS;
            } else if (state[3].clicked) {
                // End the game
                continuePlaying = false;
            }
            break;
        case INSTRUCTIONS:
        case CREDITS:
            if (state[0].clicked) {
                gameMode = START_MENU;
            } else if (state[1].clicked) {
                gameMode = GAME_ON;
            } else if (state[2].clicked) {
                continuePlaying = false;
            }
            break;
        case GAME_ON:
            if(state[0].clicked) {
                gameMode = PAUSED;
                // Pause the timers
                pauseTimers(timerPaused);
            }
            break;
        case PAUSED:
            if(state[0].clicked) {
                gameMode = GAME_ON;
            } else if (state[1].clicked) {
                unpauseTimers(timerPaused);
                gameMode = GAME_ON;
                userKeyboard.keyR = true;
            } else if (state[2].clicked) {
                gameMode = START_MENU;
                unpauseTimers(timerPaused);
                userKeyboard.keyR = true;
            } else if (state[3].clicked) {
                continuePlaying = false;
            }
            break;
    }
    // Check if game mode has changed
    checkIfNewGameMode(gameMode, previousGameMode, state);
}

/// This function exits everything for no memory loss
/// Need to pass the instruction images and the character
/// No return type
void exitProgram(Character &image, InstructionImages &displayImages) {

    //Release the bitmap data and exit with no errors
    al_destroy_bitmap(image.bitmap);
    al_destroy_bitmap(displayImages.arrowKeys);
    al_destroy_bitmap(displayImages.invinciblePowerUp);
    al_destroy_bitmap(displayImages.slowMotionPowerUp);
    al_destroy_bitmap(displayImages.tinyPowerUp);
	al_destroy_display(app.display);
	al_destroy_event_queue(app.event_queue);
	al_destroy_timer(app.timer);
	al_destroy_timer(app.speedIncreaser);
	al_destroy_timer(app.slowmoTimer);
	al_destroy_timer(app.invincibleTimer);
	al_destroy_timer(app.miniTimer);
	al_destroy_font(app.arial);
	al_destroy_font(app.smallArial);
	al_destroy_sample(app.gameMusic);
	al_destroy_sample(app.characterDeath);
	al_destroy_sample(app.buttonClick);
	al_destroy_sample(app.collision);
}
