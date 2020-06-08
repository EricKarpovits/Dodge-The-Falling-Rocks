#include "declarations.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *timer, *speedIncreaser, *slowmoTimer, *invincibleTimer, *miniTimer;
extern ALLEGRO_FONT *arial, *smallArial;
extern ALLEGRO_EVENT_QUEUE *event_queue;

//This function sets the program up
int setupMain(Character &cSetup, Lives lSetup[], Rocks rSetup[], Keyboard &kSetup, PowerUp fallingPowerUps[]){

    //Seed random number
	srand(time(0));

    int returnCode = 0;

    if(kSetup.keyR){
        al_set_timer_count(speedIncreaser, 0);
        al_stop_timer(invincibleTimer);
        al_set_timer_count(invincibleTimer, 0);
        al_stop_timer(miniTimer);
        al_set_timer_count(miniTimer, 0);
        al_stop_timer(slowmoTimer);
        al_set_timer_count(slowmoTimer, 0);
        // Create a bitmap character and load the picture
        ALLEGRO_BITMAP *characterImg = al_load_bitmap("mainCharacter.bmp");
        cSetup.bitmap = characterImg;
        if (!cSetup.bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -5;
        }
        //Remove Pink Mask
        al_convert_mask_to_alpha(cSetup.bitmap, PINK);
    }

    if(!kSetup.keyR){
        // Initialize Allegro
        al_init();
        al_init_image_addon();

        // Load images
        returnCode = loadImage(cSetup, rSetup, lSetup);
        if (returnCode != 0) {
            return returnCode;
        }

        // Initialize display
        display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
        if (!display) {
            al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }
        al_set_window_title(display, "Dodge the Falling Rocks");

        // Initialize keyboard routines
        if (!al_install_keyboard()) {
            al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -2;
        }

        // Need to add image processor
        if (!al_init_image_addon()) {
            al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -3;
        }

        // Initialize primative add on
        if (!al_init_primitives_addon()) {
            al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        if (!al_install_mouse()) {
            al_show_native_message_box(display, "Error", "Error", "Failed to initialize mouse addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        // Create FPS timer
        timer = al_create_timer(1.0 / FPS);
        // Create invincible timer
        invincibleTimer = al_create_timer(3.0);
        // Create speed increaser timer
        speedIncreaser = al_create_timer(30.0);
        // Create slowmo power up timer
        slowmoTimer = al_create_timer(5.0);
        // Create mini power up
        miniTimer = al_create_timer(5.0);
        if (!slowmoTimer || !invincibleTimer || !timer || !speedIncreaser ||!miniTimer) {
            al_show_native_message_box(display, "Error", "Error", "Failed to create timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -5;
        }

        // set up event queue
        event_queue = al_create_event_queue();
        if (!event_queue) {
            al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -11;
        }

        al_init_font_addon(); // initialize the font addon
        al_init_ttf_addon();// initialize the ttf (True Type Font) addon

        arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 25, 0);
        smallArial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 18, 0);
        if (!arial || !smallArial){
            al_show_native_message_box(display, "Error", "Error", "Could not load arial.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

         // Register Events
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_keyboard_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_mouse_event_source());

        // Start timers
        al_start_timer(timer);
    }

    // Set up the structs and initialize them
    characterSetup(cSetup);
    lifeSetup(lSetup);
    generateRockLocation(rSetup);
    initializeUserKeyboard(kSetup);
    for(int i = 0; i < NUMBER_OF_POWERUPS; i++){
        returnCode = setupPowerUps(fallingPowerUps[i]);
    }

    kSetup.keyR = false;
    return 0;
}

//This function initializes the users position
void characterSetup(Character &a){
    a.characterPositionX = 250;
    a.characterPositionY = 650;
    a.drawCharacterHit = true;
}

//This function sets up the users lives
void lifeSetup(Lives a[]){
    // Sets up their usability and the
    for(int i=0; i<NUMBER_OF_LIVES; i++){
        a[i].xCoordinate = i*40;
        a[i].yCoordinate = 0;
        a[i].usable = true;
    }
}

//This function initializes the starting locations of all the rocks
void generateRockLocation(Rocks startPosition[]){
    // Generate the location of the rock
    for (int i = 0; i < NUMBER_OF_ROCKS; i++){
         startPosition[i].rockPositionX = rand() % GENERATE_RANGE;
         startPosition[i].rockPositionY = (rand() % 1000) - 1000;
    }
}

//This function initializes the keyboard
void initializeUserKeyboard(Keyboard &initialize){

    initialize.keyUp = false;
    initialize.keyDown = false;
    initialize.keyLeft = false;
    initialize.keyRight = false;
    initialize.keySpace = false;
    initialize.keyB = false;
    initialize.keyP = false;
    initialize.xCoordinateMovement = 0;
    initialize.yCoordinateMovement = 0;
}

//This function loads the images of the bitmaps
int loadImage(Character &imageCharacter, Rocks imageRocks[], Lives imageLives[]){

     // Create a bitmap character and load the picture
    ALLEGRO_BITMAP *characterImg = al_load_bitmap("mainCharacter.bmp");
    imageCharacter.bitmap = characterImg;

    if (!imageCharacter.bitmap) {
		al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	al_destroy_display(display);
     	return -5;
    }
    //Remove Pink Mask
    al_convert_mask_to_alpha(imageCharacter.bitmap, PINK);

    //Load bitmap image of the rock
    ALLEGRO_BITMAP *rockImg = al_load_bitmap("fallingRock.bmp");

    for(int i = 0; i < NUMBER_OF_ROCKS; i++){
        // Create a bitmap of rock and load the picture
        imageRocks[i].bitmap = rockImg;
        if (!imageRocks[i].bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -(6 + i);
        }
        //Remove Pink Mask
        al_convert_mask_to_alpha(imageRocks[i].bitmap, PINK);
    }

    // Load images for every life
    for(int i = 0; i<NUMBER_OF_LIVES; i++){
        ALLEGRO_BITMAP *lifeImg = al_load_bitmap("life.bmp");
        imageLives[i].bitmap = lifeImg;
        if (!imageLives[i].bitmap) {
            al_show_native_message_box(display, "Error", "Error", "Failed to load image!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(display);
            return -(10 + i);
        }
        al_convert_mask_to_alpha(imageLives[i].bitmap, PINK);
    }
    return 0;
}

//This modular function checks if something did not load
//int checkIfImageLoaded()
