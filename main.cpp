/** Eric Karpovits - ICS3U - Dodge the falling rocks summative - June 12 2020
*   In this game the user dodges the falling rocks to obtain points.
*   Check out the instructions in game to know how to play.
*/

#include "declarations.h"
#include "prototype.h"

Application app;

/// Main
int main(int argc, char *argv[]) {

    //Declare variables
    bool continuePlaying = true;
    int returnCode = 0;
	int gameMode = START_MENU;

	//Declare struct variables
	Character mainCharacter;
	Rocks fallingRocks[NUMBER_OF_ROCKS];
    Keyboard userKeyboard;
    Paused timerPaused;
    Lives userLives[NUMBER_OF_LIVES];
    PowerUp fallingPowerUps[NUMBER_OF_POWERUPS];
    Button clickableButton [NUMBER_OF_BUTTONS];
    InstructionImages displayImages;

    // Initialize restart key bool
    userKeyboard.keyR = false;

    // Function to set up the game
    // Returns a non 0 if something went wrong
    returnCode = setupMain(mainCharacter, userLives, fallingRocks, userKeyboard, fallingPowerUps, displayImages);
    if (returnCode != 0) {
        return returnCode;
    }

    // Set up the clickable buttons
    buttonSetup(clickableButton, gameMode);

	while (continuePlaying) {
        // A play game function which allows the whole game to operate
        returnCode = playGame(
                        continuePlaying,
                        userKeyboard,
                        mainCharacter,
                        fallingRocks,
                        userLives,
                        fallingPowerUps,
                        gameMode,
                        clickableButton,
                        timerPaused,
                        displayImages);
        if (returnCode != 0) {
            return returnCode;
        }
	}

    //A function to exit the program
    exitProgram(mainCharacter, displayImages);

    return 0;
}

