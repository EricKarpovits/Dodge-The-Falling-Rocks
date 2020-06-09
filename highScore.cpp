#include "declarations.h"

extern ALLEGRO_FONT *arial;
extern ALLEGRO_DISPLAY *display;

//This function compares the existing high score with the players score to see if it is the high score.
//It stores the high score in a text file
int checkHighScore(int playerScore){

    //Declare file variable and variables
    int highScore[NUMBER_OF_HIGHSCORES] = {0};
    bool userIsHighScore = false;
    int returnCode = 0;
    FILE *fptr;

    // Open the high score file and copy the high scores
    fptr = fopen("highScore.txt", "r");
    if(!fptr){
        al_show_native_message_box(display, "Error", "Error", "Failed to load high score text file!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -11;
    }
    for(int i = 0; i < NUMBER_OF_HIGHSCORES; i++){
       fscanf(fptr, "%d", &highScore[i]);
    }
    fclose(fptr);

    // Print out the current high scores
    al_clear_to_color(SLATEGREY);
    al_draw_textf(arial, RED, 620, 0, ALLEGRO_ALIGN_RIGHT, "Score: %d", playerScore);
    al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER, "The current high score is:");
    printHighScore(highScore);
    al_flip_display();

    Sleep(3000);

    for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++){
        if(playerScore > highScore[i]){
            //This formula took forever for me to create, I had to create models and so on
            //Basically it moves every high score down one slot starting where the new high score is taking place.
            //For example if the new high score is slot number 4 then high score 5 will the previous high score 4.
            //I really did not want to hard code it because I wanted to make this program as flexible and changeable as possible
            for(int j = (NUMBER_OF_HIGHSCORES - 1); j > i; j--){
                highScore[j] = highScore[j-1];
            }

            highScore[i] = playerScore;

            //Print out the new high scores if the user obtained a high score
            al_clear_to_color(SLATEGREY);
            al_draw_textf(arial, BLACK, 0, 0, ALLEGRO_ALIGN_LEFT, "Your score is the current high score in slot %d", i + 1);
            al_draw_text(arial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER, "The new current high score is:");
            printHighScore(highScore);
            fptr = fopen("highScore.txt", "w");

            for(int i = 0; i < NUMBER_OF_HIGHSCORES; i++){
                fprintf(fptr, "%d\n", highScore[i]);
            }
            fclose(fptr);
            userIsHighScore = true;
            break;
        }
    }

    // User is not a high score
    if (!userIsHighScore){
        al_clear_to_color(SLATEGREY);
        al_draw_text(arial, BLACK, SCREEN_WIDTH /2, 100, ALLEGRO_ALIGN_CENTER, "Your score is not a high score");
    }

    // Average high score
    returnCode = averageHighscore(playerScore);
    if (returnCode != 0){
        return returnCode;
    }

    al_flip_display();
    Sleep(3000);

    return 0;
}

//`This function prints out the high scores
void printHighScore(int highScore[]){

    for(int i = 0; i < NUMBER_OF_HIGHSCORES; i++){
        al_draw_textf(arial, BLACK, SCREEN_WIDTH / 2, 140+i*30, ALLEGRO_ALIGN_CENTER,  "%d", highScore[i]);
    }
}

// This calculates the average scores in the score log plus the users score
int averageHighscore(int playerScore){

    //Declare variables and file
    int scoreFromLog = 0;
    int counter = 0;
    float averageScore = 0;
    int sum = 0;
    FILE *fptr;

    // Open and copy the scores from the file
    fptr = fopen("scoreLog.txt", "r");
    if(!fptr){
        al_show_native_message_box(display, "Error", "Error", "Failed to load score log text file!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return -11;
    }
    while (fscanf(fptr, "%d", &scoreFromLog) != EOF){
        counter ++;
        sum += scoreFromLog;
    }
    fclose(fptr);

    // Open and append the users score to the score log
    fptr = fopen("scoreLog.txt", "a");
    fprintf(fptr, "\n%d", playerScore);
    fclose(fptr);

    // Add the users current score to the sum and calculate average
    sum += playerScore;
    counter ++;
    averageScore = (float)sum / (float)counter;

    // Print average score
    al_draw_textf(arial, BLACK, SCREEN_WIDTH / 2, 25, ALLEGRO_ALIGN_CENTER, "The average score is %.2f", averageScore);

    return 0;
}




