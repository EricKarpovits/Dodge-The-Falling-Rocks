#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function sets the program up and is used if the user restarts the game
/// Need to pass all the structs
/// Int return type; 0 if no errors
int setupMain(
        Character &cSetup,
        Lives lSetup[],
        Rocks rSetup[],
        Keyboard &kSetup,
        PowerUp fallingPowerUps[],
        InstructionImages &iSetup) {

    // Seed random number
	srand(time(0));

	// Declare variable
    int returnCode = 0;

    // Check if it is a game restart
    if(!kSetup.keyR) {

        // Function to initialize Allegro
        returnCode = initializeAllegro();
        if (returnCode != 0) {
            return returnCode;
        }

        // Load instruction images
        returnCode = loadInstructionImg(iSetup);
        if (returnCode !=0) {
            return returnCode;
        }

        // Load object images
        returnCode = loadImage(cSetup, rSetup, lSetup);
        if (returnCode != 0) {
            return returnCode;
        }

    // If it is a game restart
    } else {

        // Reset timer values and stop them
        al_stop_timer(app.speedIncreaser);
        al_set_timer_count(app.speedIncreaser, 0);
        al_stop_timer(app.invincibleTimer);
        al_set_timer_count(app.invincibleTimer, 0);
        al_stop_timer(app.miniTimer);
        al_set_timer_count(app.miniTimer, 0);
        al_stop_timer(app.slowmoTimer);
        al_set_timer_count(app.slowmoTimer, 0);

        // Create a bitmap character and load the picture, plus check for errors
        cSetup.bitmap = al_load_bitmap("mainCharacter.bmp");
            if (!cSetup.bitmap) {
                al_show_native_message_box(app.display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
                al_destroy_display(app.display);
                return ERROR_CHARACTER_IMG;
            }
        //Remove Pink Mask
        al_convert_mask_to_alpha(cSetup.bitmap, PINK);
    }


    // Set up the structs and initialize them
    characterSetup(cSetup);
    lifeSetup(lSetup);
    generateRockLocation(rSetup);
    initializeUserKeyboard(kSetup);
    for (int i = 0; i < NUMBER_OF_POWERUPS; i++) {
        returnCode = setupPowerUps(fallingPowerUps[i]);
    }

    // Game restart is now false
    kSetup.keyR = false;

    return 0;
}

/// This function initializes the keyboard
/// Need to pass the keyboard struct
/// No return type
void initializeUserKeyboard(Keyboard &initialize) {

    // If it is not a game restart then no need to initialize these values as they caused the character to move in that direction
    // if the user was holding down these keys while restarting the game (weird bug)
    if (!initialize.keyR) {
        initialize.keyLeft = false;
        initialize.keyDown = false;
        initialize.keyRight = false;
        initialize.keyUp = false;
        initialize.keySpace = false;
    }

    initialize.keyB = false;
    initialize.keyP = false;
    initialize.xCoordinateMovement = 0;
    initialize.yCoordinateMovement = 0;
}

