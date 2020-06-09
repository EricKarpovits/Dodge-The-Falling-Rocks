#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_FONT *arial, *smallArial;

// This function prints out the instructions onto the screen based on the text file
int gameInstructions(){

    // Declare file and bipmaps
    FILE *fptr;
    ALLEGRO_BITMAP *invinciblePowerUp, *tinyPowerUp, *slowMotionPowerUp, *arrowKeys;

    invinciblePowerUp = al_load_bitmap("powerUpInvincibility.bmp");
    if(!invinciblePowerUp){
        al_show_native_message_box(display, "Error", "Error", "Failed to load invincible power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return ERROR_INVINCIBILITY_IMG;
    }

    tinyPowerUp = al_load_bitmap("powerUpMini.bmp");
    if(!tinyPowerUp){
        al_show_native_message_box(display, "Error", "Error", "Failed to load tiny power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_bitmap(invinciblePowerUp);
        return ERROR_INVINCIBILITY_IMG;
    }

    slowMotionPowerUp = al_load_bitmap("powerUpSlowmo.bmp");
    if(!slowMotionPowerUp){
        al_show_native_message_box(display, "Error", "Error", "Failed to load slow motion power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_bitmap(invinciblePowerUp);
        al_destroy_bitmap(tinyPowerUp);
        return ERROR_INVINCIBILITY_IMG;
    }

    arrowKeys = al_load_bitmap("arrowKeys.png");
    if(!arrowKeys){
        al_show_native_message_box(display, "Error", "Error", "Failed to load arrow keys image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_bitmap(invinciblePowerUp);
        al_destroy_bitmap(tinyPowerUp);
        al_destroy_bitmap(slowMotionPowerUp);
        return ERROR_INVINCIBILITY_IMG;
    }

    // Convert pink mask to transparent
    al_convert_mask_to_alpha(invinciblePowerUp, PINK);
    al_convert_mask_to_alpha(tinyPowerUp, PINK);
    al_convert_mask_to_alpha(slowMotionPowerUp, PINK);
    al_convert_mask_to_alpha(arrowKeys, PINK);

    // Draw the bitmaps at the appropriate spots
    al_draw_bitmap(invinciblePowerUp, 540, 250, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(slowMotionPowerUp, 540,300, ALLEGRO_ALIGN_LEFT);
    al_draw_bitmap(tinyPowerUp, 540, 350, ALLEGRO_ALIGN_CENTER);
    al_draw_bitmap(arrowKeys, 500, 100, ALLEGRO_ALIGN_CENTER);


    // Open the instructions file
    fptr = fopen("instructions.txt", "r");
    if(!fptr){
        al_show_native_message_box(display, "Error", "Error", "Failed to load instructions text file!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -11;
    }

    // This function prints out the instructions based on the
    printFromTextfile(fptr);
    fclose(fptr);

    // Destroy bitmaps for no memory leak
    al_destroy_bitmap(invinciblePowerUp);
    al_destroy_bitmap(arrowKeys);
    al_destroy_bitmap(tinyPowerUp);
    al_destroy_bitmap(slowMotionPowerUp);

    return 0;
}

// This function prints out the credits onto the screen
int credits(){

    // Declare file
    FILE *fptr;

    // Open file
    fptr = fopen("credits.txt", "r");

    if(!fptr){
        al_show_native_message_box(display, "Error", "Error", "Failed to load credits text file!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -12;
    }

    printFromTextfile(fptr);

    fclose(fptr);

    al_flip_display();

    return 0;
}

// This modular reusable function prints text from the text file based on the instructions
void printFromTextfile(FILE *fptr){

    // Declare variables
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
        }else{
            al_draw_text(smallArial, BLACK, 5, 50 + 30*smallTextCounter + 50*largeTextCounter, ALLEGRO_ALIGN_LEFT, finalInstruction);
            smallTextCounter ++;
        }
        strcpy(finalInstruction, "");
    }
}
