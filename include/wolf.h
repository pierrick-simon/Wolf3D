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

    #define WIN_HEIGHT 1080
    #define WIN_WIDTH 1920
    #define WIN_BITS 144
    #define WIN_FRAME 120
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
    #define RIGHT_ANGLE 90

    #define ORANGE sfColor_fromRGB(255, 128, 0)
    #define GREY sfColor_fromRGB(93, 93, 93)
    #define LIGHT_GREY sfColor_fromRGB(125, 125, 125)

    #define MAX_HEALTH 100

    #define __maybe_unused  __attribute__((unused))

    #define MAX_JOYSTICK 100.0

    #define MAX_SCORE 999999999

    #define MAX_AMMO 999

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
    DIFFICULTY,
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
    [DIFFICULTY] = "difficulty",
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
    unsigned int fps;
    sfBool fullscreen;
    scene_t scene;
    scene_t old_scene;
} state_info_t;

typedef struct system_s {
    sfRenderWindow *window;
    sfBool controler;
    sfMusic *music;
    background_t *background;
    textbox_t *textbox;
    state_info_t *state;
    save_t *save;
} system_t;

int check_env(char **env);

// init

sfRenderWindow *create_window(sfUint32 style, double coeff);
draw_textbox_t *init_from_conf(char *path);

// event

void sys_events(sfEvent event, system_t *sys);
sfBool is_input(sfEvent event, sfKeyCode key,
    sfBool is_joysick, unsigned int joytick_button);

void move_rect(sfSprite *sprite, sfIntRect *rect, int offset, int nb_tile);
void sys_loop(system_t *sys, void **structure);
void draw_string(system_t *sys, textbox_t *textbox, draw_textbox_t *draw);
void draw_background(system_t *sys, background_t *background);

// destroy

void destroy_struct(void **structure, int stop);
void destroy_sys(system_t *sys);
void free_draw_textbox(draw_textbox_t *draw, int stop);

#endif
