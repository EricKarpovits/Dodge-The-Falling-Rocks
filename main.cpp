/** Eric Karpovits - ICS3U - Dodge the falling rocks summative - June 12 2020
*   In this game the user dodges the falling rocks to obtain points.
*   Check out the instructions in game to know how to play.
*/

#include "declarations.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer, *speedIncreaser, *slowmoTimer, *invincibleTimer, *miniTimer;
ALLEGRO_FONT *arial, *smallArial;
ALLEGRO_EVENT_QUEUE *event_queue;

int main(int argc, char *argv[]){

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

    // Initialize restart key bool
    userKeyboard.keyR = false;

    // Function to set up the game
    // Returns a non 0 if something went wrong
    returnCode = setupMain(mainCharacter, userLives, fallingRocks, userKeyboard, fallingPowerUps);
    if (returnCode != 0) {
        printf("Returning error code %d.", returnCode);
        return returnCode;
    }

    buttonSetup(clickableButton, gameMode);

	while (continuePlaying){
        // A play game function which allows the whole game to operate
        returnCode = playGame(continuePlaying, userKeyboard, mainCharacter, fallingRocks, userLives, fallingPowerUps, gameMode, clickableButton, timerPaused);
        if (returnCode != 0) {
            printf("Returning error code %d.", returnCode);
            return returnCode;
        }
	}

    //A function to exit the program
    exitProgram(mainCharacter);

    return 0;
}

//This function exits everything for the program
void exitProgram(Character &image){
    //Release the bitmap data and exit with no errors
    al_destroy_bitmap(image.bitmap);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_timer(speedIncreaser);
	al_destroy_timer(slowmoTimer);
	al_destroy_timer(invincibleTimer);
	al_destroy_timer(miniTimer);
	al_destroy_font(arial);
}


