/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** header
*/

#ifndef HEADER_H_
    #define HEADER_H_

    #define SUCCESS 0
    #define ERROR 84
    #define SKIP -1

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

    #define VOL_MAX 100.0
    #define VOL_MIN 0.0
    #define VOL_GAP 5.0

    #define WIN_HEIGHT 1080
    #define WIN_WIDTH 1920
    #define WIN_BITS 144
    #define WIN_FRAME 60
    #define WINDOW_NAME "Wolf3D"

    #define GUY_SPRITE_X 612
    #define GUY_SPRITE_Y 408

    #define SEC_IN_MICRO 1000000
    #define MIN_IN_SEC 60

    #define TILE_SIZE 64

    #define LEFT_COLOR sfColor_fromRGB(99, 99, 99)
    #define LEFT_SHADOW sfColor_fromRGB(49, 49, 49)
    #define TOP_COLOR sfColor_fromRGB(59, 59, 59)
    #define TOP_SHADOW sfColor_fromRGB(9, 9, 9)

    #define DEG(rad) (180 / M_PI) * rad
    #define RAD(deg) (M_PI / 180) * deg

    #define SWITCH 170
    #define PAD sfColor_fromRGB(255, 230, 200)

    #define SETTING_FILL 400
    #define SETTING_OFFSET 30

    #define ORANGE sfColor_fromRGB(255, 128, 0)
    #define GREY sfColor_fromRGB(93, 93, 93)
    #define LIGHT_GREY sfColor_fromRGB(125, 125, 125)

    #define MAX_HEALTH 100

    #define __maybe_unused  __attribute__((unused))

    #define MAX_JOYSTICK 100.0

typedef enum str_menu_e {
    MENU_TITLE,
    MENU_PLAY,
    MENU_SETTINGS,
    MENU_QUIT,
    NB_MENU,
} str_menu_t;

typedef enum str_pause_e {
    PAUSE_TITLE,
    PAUSE_RESUME,
    PAUSE_RESTART,
    PAUSE_SETTINGS,
    PAUSE_BACK,
    NB_PAUSE,
} str_pause_t;

typedef enum str_setting_e {
    SETTING_ON,
    SETTING_OFF,
    SETTING_ZERO,
    SETTING_HUNDRED,
    SETTING_TITLE,
    SETTING_FULL,
    SETTING_SOUND,
    SETTING_BACK,
    NB_SETTINGS,
} str_setting_t;

typedef enum scene_s {
    GAME,
    MENU,
    SETTINGS,
    PAUSE,
    MAPS,
    MAP,
    SCORE,
    LEAVE,
    WIN,
    LOSE,
    NB_SCENE,
    QUIT,
} scene_t;

static const char *str_scene[] __maybe_unused = {
    [GAME] = "game",
    [MENU] = "menu",
    [SETTINGS] = "setting",
    [PAUSE] = "pause",
    [MAPS] = "maps",
    [MAP] = "map",
    [SCORE] = "score",
    [LEAVE] = "leave",
    [WIN] = "win",
    [LOSE] = "lose",
    [NB_SCENE] = "",
    [QUIT] = "quit",
};

typedef struct save_s save_t;

typedef struct draw_textbox_s {
    char *str;
    sfVector2f pos;
    unsigned int size;
    sfColor color;
    int scene;
} draw_textbox_t;

typedef struct sprite_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f posf;
    sfVector2f scale;
    sfIntRect rectangle;
    int tile;
} sprite_t;

typedef struct background_s {
    sfSprite *guy_s;
    sfTexture *guy_t;
    sfSprite *wallpaper_s;
    sfTexture *wallpaper_t;
} background_t;

typedef struct textbox_s {
    sfText *text;
    sfFont *font;
} textbox_t;

typedef struct state_info_s {
    double volume;
    sfBool fullscreen;
    scene_t scene;
    scene_t old_scene;
} state_info_t;

typedef struct system_s {
    sfRenderWindow *window;
    sfMusic *music;
    background_t *background;
    textbox_t *textbox;
    state_info_t *state;
    save_t *save;
} system_t;

typedef struct setting_s {
    int str;
    draw_textbox_t *draw;
    sfRectangleShape *rect;
} setting_t;

typedef struct pause_s {
    int str;
    draw_textbox_t *draw;
} pause_t;

typedef struct menu_s {
    int str;
    draw_textbox_t *draw;
} menu_t;

int check_env(char **env);

// init

void *init_menu(void);
void *init_pause(void);
void *init_settings(void);
sfRenderWindow *create_window(sfUint32 style, double coeff);
draw_textbox_t *init_from_conf(char *path);

// event

void sys_events(sfEvent event, system_t *sys);
sfBool is_input(sfEvent event, sfKeyCode key,
    sfBool is_joysick, unsigned int joytick_button);
void menu_events(system_t *sys, menu_t *menu);
void setting_events(system_t *sys, setting_t *setting);
void pause_events(system_t *sys, pause_t *pause);

void move_rect(sfSprite *sprite, sfIntRect *rect, int offset, int nb_tile);
void sys_loop(system_t *sys, void **structure);
void draw_menu(system_t *sys, void *structure);
void draw_settings(system_t *sys, void *structure);
void draw_pause(system_t *sys, void *structure);
void draw_string(system_t *sys, textbox_t *textbox, draw_textbox_t *draw);
void draw_background(system_t *sys, background_t *background);

// destroy

void destroy_struct(void **structure, int stop);
void destroy_sys(system_t *sys);
void destroy_menu(void *structure);
void destroy_pause(void *structure);
void destroy_settings(void *structure);
void free_draw_textbox(draw_textbox_t *draw, int stop);

#endif
