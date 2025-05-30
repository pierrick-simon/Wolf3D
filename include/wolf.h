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
    LEVELS,
    MAP,
    SCORE,
    LEAVE,
    WIN,
    LOSE,
    DIFFICULTY,
    NB_SCENE,
    QUIT,
} scene_t;

typedef enum config_e {
    CONF_DIFFICULTY,
    CONF_LEAVE,
    CONF_LOSE,
    CONF_MAP,
    CONF_LEVELS,
    CONF_MENU,
    CONF_PAUSE,
    CONF_SCORE,
    CONF_SETTINGS,
    CONF_TOOLBAR,
    CONF_WIN,
    CONF_WEAPON,
} config_t;

typedef enum asset_e {
    WALLS_ASSET,
    HEAD_ASSET,
    FLASHLIGHT_ASSET,
    TOOLBAR_ASSET,
    BORDER_ASSET,
    EMPTY_ASSET,
    FONT_ASSET,
    GUY_ASSET,
    WALLPAPER_ASSET,
    MENU_MUSIC_ASSET,
    SPIN_ASSET,
    DANSE_ASSET,
} asset_t;

static const char *str_scene[] __maybe_unused = {
    [GAME] = "game",
    [MENU] = "menu",
    [SETTINGS] = "setting",
    [PAUSE] = "pause",
    [LEVELS] = "maps",
    [MAP] = "map",
    [SCORE] = "score",
    [LEAVE] = "leave",
    [WIN] = "win",
    [LOSE] = "lose",
    [DIFFICULTY] = "difficulty",
    [NB_SCENE] = "",
    [QUIT] = "quit",
};

static const char *str_conf[] __maybe_unused = {
    [CONF_DIFFICULTY] = "config_file/difficulty.conf",
    [CONF_LEAVE] = "config_file/leave.conf",
    [CONF_LOSE] = "config_file/lose.conf",
    [CONF_MAP] = "config_file/map.conf",
    [CONF_LEVELS] = "config_file/maps.conf",
    [CONF_MENU] = "config_file/menu.conf",
    [CONF_PAUSE] = "config_file/pause.conf",
    [CONF_SCORE] = "config_file/score.conf",
    [CONF_SETTINGS] = "config_file/setting.conf",
    [CONF_TOOLBAR] = "config_file/toolbar.conf",
    [CONF_WIN] = "config_file/win.conf",
    [CONF_WEAPON] = "config_file/weapon.conf",
};

static const char *str_asset[] __maybe_unused = {
    [WALLS_ASSET] = "asset/walls.png",
    [HEAD_ASSET] = "asset/head.png",
    [FLASHLIGHT_ASSET] = "asset/flashlight.png",
    [TOOLBAR_ASSET] = "asset/toolbar.png",
    [BORDER_ASSET] = "asset/minimap_border.png",
    [EMPTY_ASSET] = "asset/empty.ogg",
    [FONT_ASSET] = "asset/font.ttf",
    [GUY_ASSET] = "asset/doom_guy.png",
    [WALLPAPER_ASSET] = "asset/wallpaper.png",
    [MENU_MUSIC_ASSET] = "asset/menu_music.ogg",
    [SPIN_ASSET] = "asset/spin_chair.png",
    [DANSE_ASSET] = "asset/danse.png",
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
    char *dir;
} system_t;

int check_env(char **env);

// init

sfRenderWindow *create_window(sfUint32 style, double coeff);
draw_textbox_t *init_from_conf(const char *path);

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
