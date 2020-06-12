#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function compares the existing high score with the players score to see if it is the high score.
/// It stores the high score in a text file
/// Need to pass the users score
/// Int return type
int checkHighScore(int playerScore) {

    //Declare file variable and variables
    int highScore[NUMBER_OF_HIGHSCORES] = {0};
    bool userIsHighScore = false;
    int returnCode = 0;
    FILE *fptr;

    // Open the high score file and copy the high scores
    fptr = fopen("highScore.txt", "r");
    returnCode = checkIfFileLoaded(fptr);
    if (returnCode != 0) {
        return returnCode;
    }
    for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++) {
       fscanf(fptr, "%d", &highScore[i]);
    }
    fclose(fptr);

    // Print out the current high scores
    al_clear_to_color(SLATEGREY);
    al_draw_textf(app.arial, RED, 620, 0, ALLEGRO_ALIGN_RIGHT, "Score: %d", playerScore);
    al_draw_text(app.arial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER, "The current high score is:");
    printHighScore(highScore);
    al_flip_display();

    Sleep(8000);

    for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++) {
        if (playerScore > highScore[i]) {
            // This formula took forever for me to create, I had to create models and so on
            // Basically it moves every high score down one slot starting where the new high score is taking place.
            // For example if the new high score is slot number 4 then high score 5 will the previous high score 4.
            // I really did not want to hard code it because I wanted to make this program as flexible and changeable as possible
            for (int j = (NUMBER_OF_HIGHSCORES - 1); j > i; j--) {
                highScore[j] = highScore[j-1];
            }

            highScore[i] = playerScore;

            // Print out the new high scores if the user obtained a high score
            al_clear_to_color(SLATEGREY);
            al_draw_textf(app.arial, RED, SCREEN_WIDTH / 2, 25, ALLEGRO_ALIGN_CENTER, "Your score is the new high score in slot %d", i + 1);
            al_draw_text(app.arial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER, "The new current high score is:");
            printHighScore(highScore);

            // Print out the new high scores into the text file
            fptr = fopen("highScore.txt", "w");
            returnCode = checkIfFileLoaded(fptr);
            if (returnCode != 0){
                return returnCode;
            }
            for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++) {
                fprintf(fptr, "%d\n", highScore[i]);
            }
            fclose(fptr);

            userIsHighScore = true;
            al_flip_display();
            Sleep(10000);
            break;
        }
    }

    // User is not a high score
    if (!userIsHighScore) {
        al_clear_to_color(SLATEGREY);
        al_draw_text(app.arial, BLACK, SCREEN_WIDTH /2, 100, ALLEGRO_ALIGN_CENTER, "Your score is not a high score");
        al_flip_display();
        Sleep(5000);
    }

    al_clear_to_color(SLATEGREY);

    // Find the average high score
    returnCode = averageHighscore(playerScore);
    if (returnCode != 0) {
        return returnCode;
    }
    al_flip_display();

    return 0;
}

///`This function prints out the high scores
/// Need to pass the high score
/// No return type
void printHighScore(int highScore[]) {

    for (int i = 0; i < NUMBER_OF_HIGHSCORES; i++) {
        al_draw_textf(app.arial, BLACK, SCREEN_WIDTH / 2, 140+i*30, ALLEGRO_ALIGN_CENTER,  "%d", highScore[i]);
    }
}

/// This calculates the average scores in the score log plus the users current score
/// Need to pass the players score
/// Int return type
int averageHighscore(int playerScore) {

    //Declare variables and file
    int scoreFromLog = 0;
    int counter = 0;
    float averageScore = 0;
    int sum = 0;
    int returnCode = 0;
    FILE *fptr;

    // Open and copy the scores from the file
    fptr = fopen("scoreLog.txt", "r");
    returnCode = checkIfFileLoaded(fptr);
    if (returnCode != 0){
        return returnCode;
    }

    while (fscanf(fptr, "%d", &scoreFromLog) != EOF) {
        counter ++;
        sum += scoreFromLog;
    }
    fclose(fptr);

    // Open and append the users score to the score log
    fptr = fopen("scoreLog.txt", "a");
    returnCode = checkIfFileLoaded(fptr);
    if (returnCode != 0) {
        return returnCode;
    }
    fprintf(fptr, "\n%d", playerScore);
    fclose(fptr);

    // Add the users current score to the sum and calculate average
    sum += playerScore;
    counter ++;
    averageScore = (float)sum / (float)counter;

    // Print average score
    al_draw_textf(app.arial, BLACK, SCREEN_WIDTH / 2, 100, ALLEGRO_ALIGN_CENTER, "The average overall score is %.2f", averageScore);

    return 0;
}




