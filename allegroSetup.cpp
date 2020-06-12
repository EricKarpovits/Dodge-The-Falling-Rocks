#include "declarations.h"
#include "prototype.h"

extern Application app;

/// This function initializes Allegro
/// No need to pass anything
/// Int return type
int initializeAllegro() {

        // Initialize Allegro, image and audio add ons
        if (!al_init()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize Allegro5!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_ALLEGRO;
        }

        if (!al_init_image_addon()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize image addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_IMAGE_ADDON;
        }

        if (!al_install_audio()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to install audio!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_INSTALL_AUDIO;
        }

        if (!al_init_acodec_addon()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize acodec addon!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_ACODEC_ADDON;
        }

        // Reserve space and load music files
        al_reserve_samples(NUMBER_OF_MUSIC_SAMPLES);
        app.characterDeath = al_load_sample("characterDeath.wav");
        app.gameMusic = al_load_sample("gameMusic.wav");
        app.buttonClick = al_load_sample("buttonClick.wav");
        app.collision = al_load_sample("collision.wav");

        // Check that the music files loaded
        if (!app.characterDeath) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load characterDeat.wav", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_MUSIC_FILE_CHARACTER_DEATH;
        }
        if (!app.gameMusic) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load gameMusic.wav!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_MUSIC_FILE_GAMEMUSIC;
        }
        if (!app.buttonClick) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load buttonClick.wav!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_MUSIC_FILE_BUTTONCLICK;
        }
        if (!app.collision) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to load collision.wav!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_MUSIC_FILE_COLLISION;
        }

        al_play_sample(app.gameMusic, 1.0, 0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);

        // Initialize display
        app.display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
        if (!app.display) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize display!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_DISPLAY;
        }

        // Title the window
        al_set_window_title(app.display, "Dodge the Falling Rocks");

        // Initialize keyboard routines
        if (!al_install_keyboard()) {
            al_show_native_message_box(app.display, "Error", "Error", "failed to initialize the keyboard!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_KEYBOARD;
        }

        // Need to add image processor
        if (!al_init_image_addon()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize image add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_IMG_ADDON;
        }

        // Initialize primative add on
        if (!al_init_primitives_addon()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize primatives add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_PRIMATIVE_ADDON;
        }

        // Install mouse
        if (!al_install_mouse()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize mouse add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_MOUSE_ADDON;
        }

        /// Create timers
        app.timer = al_create_timer(1.0 / FPS);
        app.invincibleTimer = al_create_timer(5.0);
        app.speedIncreaser = al_create_timer(30.0);
        app.slowmoTimer = al_create_timer(5.0);
        app.miniTimer = al_create_timer(5.0);
        app.displayTimer = al_create_timer(8.0);

        // Check that timers were created
        if (!app.slowmoTimer) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create slow motion timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_SLOW_MOTION_TIMER;
        }
        if (!app.invincibleTimer) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create invincible timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_INVINCIBLE_TIMER;
        }
        if (!app.timer) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create FPS timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_FPSTIMER;
        }
        if (!app.speedIncreaser) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create object speed increaser timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            al_destroy_display(app.display);
            return ERROR_SPEED_INCREASER_TIMER;
        }
        if (!app.miniTimer) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create mini character timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_TINY_TIMER;
        }
        if (!app.displayTimer) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create display switch timer!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_DISPLAY_TIMER;
        }

        // Start timer
        al_start_timer(app.timer);

        // Font add on
        if (!al_init_font_addon()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize font add on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_FONT_ADDON;
        }

        // initialize the ttf (True Type Font) addon
        if (!al_init_ttf_addon()) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to initialize font ttf on!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_TTF_ADDON;
        }

        // Load the fonts
        app.arial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 25, 0);
        app.smallArial = al_load_ttf_font("C:/Windows/Fonts/arial.ttf", 18, 0);

        // Check that the fonts were creates
        if (!app.arial) {
            al_show_native_message_box(app.display, "Error", "Error", "Could not load arial.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_ARIAL_FONT;
        }
        if (!app.smallArial) {
            al_show_native_message_box(app.display, "Error", "Error", "Could not create a small version of arial.ttf", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_SMALL_ARIAL_FONT;
        }

        // Set up event queue
        app.event_queue = al_create_event_queue();
        if (!app.event_queue) {
            al_show_native_message_box(app.display, "Error", "Error", "Failed to create event_queue!", nullptr, ALLEGRO_MESSAGEBOX_ERROR);
            al_destroy_display(app.display);
            return ERROR_EVENT_QUEUE;
        }

        // Register Events
        al_register_event_source(app.event_queue, al_get_display_event_source(app.display));
        al_register_event_source(app.event_queue, al_get_keyboard_event_source());
        al_register_event_source(app.event_queue, al_get_timer_event_source(app.timer));
        al_register_event_source(app.event_queue, al_get_mouse_event_source());

        return 0;
}
