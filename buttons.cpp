#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function setups the buttons coordinates based on the game mode the user is in
/// Need to pass the button struct and the game mode
/// No return type
void buttonSetup(Button setup[], int gameMode) {

    // Switch the game mode so that the buttons are set up in the appropriate game mode
    switch (gameMode) {
        case START_MENU:
        case PAUSED:
            for (int i=0; i < NUMBER_OF_BUTTONS; i++) {
                // Pass the coordinates for the function to initialize those coordinates to the button
                setButtonCoords(setup[i], SCREEN_WIDTH / 4, 150 + i*150, SCREEN_WIDTH / 4*3, 250 + i*150);
            }
            break;
        case INSTRUCTIONS:
        case CREDITS:
            for (int i=0; i < NUMBER_OF_BUTTONS - 1; i++) {
                setButtonCoords(setup[i], SCREEN_WIDTH / 10 - 35 + i*200, 700, (SCREEN_WIDTH / 10 * 3.2) + i*200, 775);
            }
            break;
        case GAME_ON:
            setButtonCoords(setup[0], SCREEN_WIDTH - 90, SCREEN_HEIGHT - 30, SCREEN_WIDTH, SCREEN_HEIGHT);
            break;
    }

    // Reset the button bools
    for (int i=0; i<NUMBER_OF_BUTTONS; i++) {
        setup[i].clicked = false;
        setup[i].filled = false;
    }
}

/// This reusable function takes the coordinates from the button setup and allocates them to each specific button
/// Need to pass the button, and the 4 coordinates
/// No return type
void setButtonCoords(Button &button, int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY) {

	button.upperLeftXCoordinate = upperLeftX;
	button.upperLeftYCoordinate = upperLeftY;
	button.lowerRightYCoordinate = lowerRightY;
	button.lowerRightXCoordinate = lowerRightX;

}

/// This function draws the buttons
/// The button is either drawn with just the outline or filled in, based on the users mouses position
/// Need to pass the button and the game mode
/// No return type
void drawButtons(Button draw[], int gameMode) {

    // Declare variables
    char buttonTitle[100];

    // Set background colour
    al_clear_to_color(SLATEGREY);

    // Switch the game mode
    switch (gameMode) {
        case START_MENU:
            for (int i=0; i<NUMBER_OF_BUTTONS; i++) {
                // Based on if the bool is true or not either it draws the box filled or just the outline
                if (!draw[i].filled) {
                    al_draw_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE, 3);
                } else {
                    al_draw_filled_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE);
                }
                // Switch the button number to the specific text
                switch (i) {
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
                // Draw out the button text
                al_draw_text(app.arial, BLACK, SCREEN_WIDTH / 2, draw[i].upperLeftYCoordinate + 37.5, ALLEGRO_ALIGN_CENTER, buttonTitle);
            }
            break;
        // Same idea as above
        case INSTRUCTIONS:
        case CREDITS:
            for (int i=0; i<NUMBER_OF_BUTTONS-1; i++) {
                if (!draw[i].filled) {
                    al_draw_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE, 3);
                } else {
                    al_draw_filled_rectangle(draw[i].upperLeftXCoordinate, draw[i].upperLeftYCoordinate, draw[i].lowerRightXCoordinate, draw[i].lowerRightYCoordinate, WHITE);
                }
                switch (i) {
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
                al_draw_text(app.arial, BLACK, (draw[i].upperLeftXCoordinate + draw[i].lowerRightXCoordinate) / 2, draw[i].upperLeftYCoordinate + 25, ALLEGRO_ALIGN_CENTER, buttonTitle);
            }
            break;
        // Same idea as above
        case GAME_ON:
            if (!draw[0].filled) {
                al_draw_rectangle(draw[0].upperLeftXCoordinate, draw[0].upperLeftYCoordinate, draw[0].lowerRightXCoordinate, draw[0].lowerRightYCoordinate, WHITE, 3);
            } else {
                al_draw_filled_rectangle(draw[0].upperLeftXCoordinate, draw[0].upperLeftYCoordinate, draw[0].lowerRightXCoordinate, draw[0].lowerRightYCoordinate, WHITE);
            }
            strcpy(buttonTitle, "PAUSE");
            al_draw_text(app.smallArial, BLACK, (draw[0].upperLeftXCoordinate + draw[0].lowerRightXCoordinate) / 2, draw[0].upperLeftYCoordinate + 7, ALLEGRO_ALIGN_CENTER, buttonTitle);
            break;
        case PAUSED:
            for (int i=0; i<NUMBER_OF_BUTTONS; i++) {
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
                al_draw_text(app.arial, BLACK, SCREEN_WIDTH / 2, draw[i].upperLeftYCoordinate + 37.5, ALLEGRO_ALIGN_CENTER, buttonTitle);
            }
            break;
    }
}

/// This function checks if the users mouse is hovering over the button and if the button was clicked
/// Need to pass the button, the mouse coordinates, game mode, and the event type (as a bool clicked or not)
/// No return type
void checkWhichButtonAction(Button check[], int mouseXCoordinate, int mouseYCoordinate, int gameMode, bool buttonClicked) {

    for (int i=0; i < NUMBER_OF_BUTTONS; i++) {
        // Check the mouse is hovering over the button
        if (mouseXCoordinate >= check[i].upperLeftXCoordinate && mouseXCoordinate <= check[i].lowerRightXCoordinate && mouseYCoordinate >= check[i].upperLeftYCoordinate && mouseYCoordinate <= check[i].lowerRightYCoordinate) {
            check[i].filled = true;
            // Check if the event tyoe was a button click
            if (buttonClicked) {
                check[i].clicked = true;
            }
        // If the mouse is not hovering over any buttons then the buttons will just be hallow
        } else {
            check[i].filled = false;
        }
    }
}


/// This function checks if the game mode was switched in order to re setup the buttons
/// Need to pass the newest game mode, the previous game mode, and the button struct array
/// No return type
void checkIfNewGameMode(int newGameMode, int previousGameMode, Button b[]) {

    if (newGameMode != previousGameMode) {
        buttonSetup(b, newGameMode);
    }
}
