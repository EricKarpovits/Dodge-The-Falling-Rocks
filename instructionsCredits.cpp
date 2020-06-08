#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *arial, *smallArial;

int gameInstructions(){
    FILE *fptr;

    ALLEGRO_BITMAP *invinciblePowerUp, *tinyPowerUp, *slowMotionPowerUp, *arrowKeys;

    invinciblePowerUp = al_load_bitmap("powerUpInvincibility.bmp");
    tinyPowerUp = al_load_bitmap("powerUpMini.bmp");
    slowMotionPowerUp = al_load_bitmap("powerUpSlowmo.bmp");
    arrowKeys = al_load_bitmap("arrowKeys.png");

    if(!arrowKeys || !tinyPowerUp || !slowMotionPowerUp ||!invinciblePowerUp){
        al_show_native_message_box(display, "Error", "Error", "Failed to load images for instructions!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -10;
    }

    al_convert_mask_to_alpha(invinciblePowerUp, PINK);
    al_convert_mask_to_alpha(tinyPowerUp, PINK);
    al_convert_mask_to_alpha(slowMotionPowerUp, PINK);
    al_convert_mask_to_alpha(arrowKeys, PINK);

    al_draw_bitmap(invinciblePowerUp, 540, 250, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(slowMotionPowerUp, 540,300, ALLEGRO_ALIGN_LEFT);
    al_draw_bitmap(tinyPowerUp, 540, 350, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(arrowKeys, 500, 100, ALLEGRO_ALIGN_CENTER);

    // Open the high score file and copy the high scores
    fptr = fopen("instructions.txt", "r");
    printFromTextfile(fptr);
    fclose(fptr);

    al_flip_display();
    return 0;
}
void credits(){
    FILE *fptr;

    fptr = fopen("credits.txt", "r");
    printFromTextfile(fptr);
    fclose(fptr);

    al_flip_display();
}

// This modular function prints text from the text file based on the instructions
void printFromTextfile(FILE *fptr){
    int numOfWords = 0;
    char instructionWord[100] = "";
    char finalInstruction[300] = "";
    int smallTextCounter = 0, largeTextCounter = 0;
    while (fscanf(fptr, "%d", &numOfWords) != EOF){
        for(int i=0; i<numOfWords; i++){
            fscanf(fptr, "%s", instructionWord);
            strcat(finalInstruction, instructionWord);
            if(i<numOfWords-1){
                strcat(finalInstruction, " ");
            }
        }
        if(numOfWords <= 2){
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 60 + 170*largeTextCounter, ALLEGRO_ALIGN_CENTRE, finalInstruction);
            largeTextCounter ++;
      } else {
            al_draw_text(smallArial, BLACK, 5, 50 + 30*smallTextCounter + 50*largeTextCounter, ALLEGRO_ALIGN_LEFT, finalInstruction);
            smallTextCounter ++;
        }
        strcpy(finalInstruction, "");
    }
}
