//Eric Karpovits - ICS3U - Dodge the falling rocks summative

#include "declarations.h"

ALLEGRO_DISPLAY *display;
ALLEGRO_TIMER *timer, *speedIncreaser, *slowmoTimer, *invincibleTimer, *miniTimer;
ALLEGRO_FONT *arial, *smallArial;
ALLEGRO_EVENT_QUEUE *event_queue;
Paused timerPaused;

int main(int argc, char *argv[]){

    //Declare variables
    bool continuePlaying = true;
    int returnCode = 0;
	int userScore = 0;
	int numberOfCollisions = 0;
	bool closedDisplay = false;
	int gameMode = 1;

	//Declare struct variables
	Character mainCharacter;
	Rocks fallingRocks[NUMBER_OF_ROCKS];
    Keyboard userKeyboard;
    Lives userLives[NUMBER_OF_LIVES];
    PowerUp fallingPowerUps[NUMBER_OF_POWERUPS];
    Button clickableButton [NUMBER_OF_BUTTONS];

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
        returnCode = playGame(continuePlaying, closedDisplay, userScore, numberOfCollisions, userKeyboard, mainCharacter, fallingRocks, userLives, fallingPowerUps, gameMode, clickableButton);
        if (returnCode != 0) {
            printf("Returning error code %d.", returnCode);
            return returnCode;
        }
	}

    //A function to exit the program
    returnCode = exitProgram(mainCharacter);
    if(returnCode == 0){
        return 0;
    }
}

//This function exits everything for the program
int exitProgram(Character &image){
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
	return 0;
}


