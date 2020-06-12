#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function initializes the users position
/// Need to pass the character struct
/// No return type
void characterSetup(Character &a) {
    a.characterPositionX = 250;
    a.characterPositionY = 650;
    a.drawCharacterHit = false;
}

/// This function sets up the users lives
/// Need to pass the lives struct array
/// No return type
void lifeSetup(Lives a[]) {
    // Sets up their usability and the
    for (int i=0; i<NUMBER_OF_LIVES; i++) {
        a[i].xCoordinate = i*40;
        a[i].yCoordinate = 0;
        a[i].usable = true;
    }
}

/// This function initializes the starting locations of all the rocks
/// Need to pass the rock array struct
/// No return type
void generateRockLocation(Rocks startPosition[]) {
    // Generate the location of the rock
    for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
         startPosition[i].rockPositionX = rand() % GENERATE_RANGE;
         startPosition[i].rockPositionY = (rand() % 1000) - 1000;
    }
}

/// This function loads the images of the bitmaps
/// Need to pass the movable object structs
/// Int return type
int loadImage(Character &imageCharacter, Rocks imageRocks[], Lives imageLives[]) {

     // Create a bitmap character and load the picture
    imageCharacter.bitmap = al_load_bitmap("mainCharacter.bmp");

    // Check if the image loaded
    if (!imageCharacter.bitmap) {
		al_show_native_message_box(app.display, "Error", "Error", "Failed to load character image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(app.display);
     	return ERROR_CHARACTER_IMG;
    }
    //Remove Pink Mask
    al_convert_mask_to_alpha(imageCharacter.bitmap, PINK);

    //Load bitmap image of the rock
    ALLEGRO_BITMAP *rockImg = al_load_bitmap("fallingRock.bmp");

    for (int i = 0; i < NUMBER_OF_ROCKS; i++) {
        // Create a bitmap of rock and load the picture
        imageRocks[i].bitmap = rockImg;
        if (!imageRocks[i].bitmap) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load rock image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_ROCK_IMG;
        }
        //Remove Pink Mask
        al_convert_mask_to_alpha(imageRocks[i].bitmap, PINK);
    }
    // Note: that I tried to destroy the rockImg after for no memory leaks, however my game would just crash

    ALLEGRO_BITMAP *lifeImg = al_load_bitmap("life.bmp");
    // Load images for every life
    for (int i = 0; i<NUMBER_OF_LIVES; i++) {
        imageLives[i].bitmap = lifeImg;
        if (!imageLives[i].bitmap) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load life image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_LIFE_IMG;
        }
        al_convert_mask_to_alpha(imageLives[i].bitmap, PINK);
    }

    return 0;
}

/// This function loads the images for the instructions
/// Need to pass the instructions struct
/// Int return type
int loadInstructionImg(InstructionImages &i){

    // Load the images for each appropriate bitmap and check for errors
    i.invinciblePowerUp = al_load_bitmap("powerUpInvincibility.bmp");
    if (!i.invinciblePowerUp) {
        al_show_native_message_box(app.display, "Error", "Error", "Failed to load invincible power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(app.display);
        return ERROR_INVINCIBILITY_IMG;
    }

    i.tinyPowerUp = al_load_bitmap("powerUpMini.bmp");
    if (!i.tinyPowerUp) {
        al_show_native_message_box(app.display, "Error", "Error", "Failed to load tiny power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(app.display);
        return ERROR_INVINCIBILITY_IMG;
    }

    i.slowMotionPowerUp = al_load_bitmap("powerUpSlowmo.bmp");
    if (!i.slowMotionPowerUp) {
        al_show_native_message_box(app.display, "Error", "Error", "Failed to load slow motion power up image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(app.display);
        return ERROR_INVINCIBILITY_IMG;
    }

    i.arrowKeys = al_load_bitmap("arrowKeys.png");
    if (!i.arrowKeys) {
        al_show_native_message_box(app.display, "Error", "Error", "Failed to load arrow keys image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(app.display);
        return ERROR_INVINCIBILITY_IMG;
    }

    // Convert pink mask to transparent
    al_convert_mask_to_alpha(i.invinciblePowerUp, PINK);
    al_convert_mask_to_alpha(i.tinyPowerUp, PINK);
    al_convert_mask_to_alpha(i.slowMotionPowerUp, PINK);
    al_convert_mask_to_alpha(i.arrowKeys, PINK);

    return 0;
}
