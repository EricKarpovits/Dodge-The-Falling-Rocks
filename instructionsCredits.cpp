#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function prints out the instructions onto the screen based on the text file
/// Need to pass the instruction images
/// Int return type
int gameInstructions(InstructionImages &draw) {

    // Declare file and bipmaps
    FILE *fptr;
    int returnCode;

    // Draw the bitmaps at the appropriate spots
    al_draw_bitmap(draw.invinciblePowerUp, 540, 250, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(draw.slowMotionPowerUp, 540,300, ALLEGRO_ALIGN_LEFT);
    al_draw_bitmap(draw.tinyPowerUp, 540, 350, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(draw.arrowKeys, 500, 100, ALLEGRO_ALIGN_CENTER);


    // Open the instructions file
    fptr = fopen("instructions.txt", "r");
    returnCode = checkIfFileLoaded(fptr);
    if (returnCode != 0) {
        return returnCode;
    }
    // This function prints out the instructions based on the
    printFromTextfile(fptr);
    fclose(fptr);

    return 0;
}

/// This function prints out the credits onto the screen based on the text file
/// No need to pass anything
/// Int return type
int credits(){

    // Declare file
    FILE *fptr;
    int returnCode;

    // Open file
    fptr = fopen("credits.txt", "r");
    returnCode = checkIfFileLoaded(fptr);
    if (returnCode != 0) {
        return returnCode;
    }
    printFromTextfile(fptr);
    fclose(fptr);
    al_flip_display();

    return 0;
}

/// This modular reusable function prints text from the text file based on the instructions from the text file
/// Need to pass the opened file
/// No return type
void printFromTextfile(FILE *fptr){

    // Declare variables
    int numOfWords = 0;
    char instructionWord[100] = "";
    char finalInstruction[300] = "";
    int smallTextCounter = 0, largeTextCounter = 0;

    // Scan how many works are in the line
    while (fscanf(fptr, "%d", &numOfWords) != EOF) {
        // Based on the number of works continue to scan them and cat each of them together
        for (int i=0; i<numOfWords; i++) {
            fscanf(fptr, "%s", instructionWord);
            strcat(finalInstruction, instructionWord);
            if (i < numOfWords-1) {
                strcat(finalInstruction, " ");
            }
        }

        // Print out with using the appropriate coordinates and size
        if (numOfWords <= 2) {
            al_draw_text(app.arial, BLACK, SCREEN_WIDTH / 2, 60 + 170*largeTextCounter, ALLEGRO_ALIGN_CENTRE, finalInstruction);
            largeTextCounter ++;
        } else {
            al_draw_text(app.smallArial, BLACK, 5, 50 + 30*smallTextCounter + 50*largeTextCounter, ALLEGRO_ALIGN_LEFT, finalInstruction);
            smallTextCounter ++;
        }
        strcpy(finalInstruction, "");
    }
}
