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
    #define WIN_NAME "Wolf3D"

    #define SEC_IN_MICRO 1000000

    #define WEAPON_FRAME 0.05
    #define WEAPON_NB_TILE 5
    #define WEAPON_SPRITE_X 320
    #define WEAPON_SPRITE_Y 180
    #define NB_WEAPON 3

    #define TILE_SIZE 64
    #define MAP_WIDTH 24
    #define MAP_HEIGHT 24

    #define FOV RAD(59)
    #define NUM_RAYS WIN_WIDTH

    #define CEILING_COLOR sfColor_fromRGB(199, 199, 199)
    #define FLOOR_COLOR sfColor_fromRGB(149, 149, 149)
    #define TOOLBAR_COLOR sfColor_fromRGB(49, 49, 49)

    #define LEFT_COLOR sfColor_fromRGB(99, 99, 99)
    #define LEFT_SHADOW sfColor_fromRGB(49, 49, 49)
    #define TOP_COLOR sfColor_fromRGB(59, 59, 59)
    #define TOP_SHADOW sfColor_fromRGB(9, 9, 9)

    #define DEG(rad) (180 / M_PI) * rad
    #define RAD(deg) (M_PI / 180) * deg

    #define MAX_DISTANCE 100.0

    #define RENDER_DISTANCE 1200

    #define PLAYER_SPEED 100
    #define ROTATION_SPEED RAD(100)
    #define FORWARD_COEF 1.5

    #define DISTANCE_COLISION 5.0

    #define NB_DECIMAL_FLOAT_CMP 6

    #define SPRINT_COEF 1.1
    #define SPRINTING_FOV FOV * SPRINT_COEF
    #define TOOLBAR_POS (WIN_HEIGHT - 130)

    #define GUY_SPRITE_X 612
    #define GUY_SPRITE_Y 408

    #define SIZE_TEXT 250

    #define CROSSAIR_RADIUS 0.1

    #define SWITCH 170
    #define PAD sfColor_fromRGB(255, 230, 200)

    #define SETTING_FILL 400
    #define SETTING_OFFSET 30

    #define __maybe_unused  __attribute__((unused))

typedef enum str_menu_e {
    MENU_TITLE,
    MENU_PLAY,
    MENU_SETTING,
    MENU_QUIT,
    NB_MENU,
} str_menu_t;

typedef enum str_setting_e {
    SETTING_ON,
    SETTING_OFF,
    SETTING_ZERO,
    SETTING_HUNDRED,
    SETTING_TITLE,
    SETTING_FULL,
    SETTING_SOUND,
    SETTING_BACK,
    NB_SETTING,
} str_setting_t;

typedef enum intersection_type {
    NONE,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
} intersection_type_t;

typedef enum {
    PUNCH,
    PISTOL,
    SHOTGUN,
} weapon_id_t;

typedef enum scene_s {
    GAME,
    MENU,
    SETTING,
    NB_SCENE,
    QUIT,
} scene_t;

static const char *str_scene[] __maybe_unused = {
    [GAME] = "game",
    [MENU] = "menu",
    [SETTING] = "setting",
    [NB_SCENE] = "",
    [QUIT] = "quit",
};

typedef struct sprite_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f posf;
    sfVector2f scale;
    sfIntRect rectangle;
    int tile;
} sprite_t;

typedef struct weapon_s {
    sprite_t *sprite;
    sfTexture **texture;
    sfMusic **sound;
    sfInt64 shot;
    int weapon;
} weapon_t;

typedef struct map_s {
    sfRectangleShape *ceiling_floor;
    sfVertexArray *rays;
    sfRenderStates wall_state;
} map_t;

typedef struct crossair_s {
    sfRenderStates state;
    sfCircleShape *circle;
} crossair_t;

typedef struct player_s {
    sfVector2f pos;
    float angle;
    sfVector2f v;
    intersection_type_t type;
    float fov;
    sfBool is_sprinting;
    crossair_t *crossair;
} player_t;

typedef struct time_info_s {
    sfClock *clock;
    sfInt64 prev_time;
    sfInt64 time;
    double delta;
} time_info_t;

typedef struct game_s {
    map_t *map;
    player_t *player;
    weapon_t *weapon;
    time_info_t *time_info;
} game_t;

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

typedef struct system_s {
    sfRenderWindow *window;
    sfMusic *music;
    sfBool fullscreen;
    int scene;
    background_t *background;
    textbox_t *textbox;
    double volume;
} system_t;

typedef struct draw_textbox_s {
    char *str;
    sfVector2f pos;
    unsigned int size;
    sfColor color;
    int scene;
} draw_textbox_t;

typedef struct setting_s {
    int str;
    draw_textbox_t *draw;
    sfRectangleShape *rect;
} setting_t;

typedef struct menu_s {
    int str;
    draw_textbox_t *draw;
} menu_t;

static const int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 8},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 8, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 8},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// init

void *init_game(void);
int init_system(system_t *sys);
void **init_struct(void);
void *init_menu(void);
void *init_setting(void);
sfRenderWindow *create_window(sfUint32 style, double coeff);
draw_textbox_t *init_from_conf(char *path);

// event

void game_events(system_t *sys, game_t *game);
void sys_events(sfEvent event, system_t *sys);
sfBool is_keyboard_input(sfEvent event, sfKeyCode key);
void menu_events(system_t *sys, menu_t *menu);
void setting_events(system_t *sys, setting_t *setting);

void move_rect(sprite_t *sprite, int offset, int max_value);
void sys_loop(system_t *sys, void **structure);
void cast_all_rays(game_t *game);
float cast_single_ray(player_t *player,
    float angle_offset, intersection_type_t *type);
void move_player(player_t *player, double delta);
void draw_game(system_t *sys, void *structure);
void draw_menu(system_t *sys, void *structure);
void draw_setting(system_t *sys, void *structure);

void draw_string(system_t *sys, textbox_t *textbox, draw_textbox_t *draw);
void draw_background(system_t *sys, background_t *background);

// destroy

void destroy_struct(void **structure, int stop);
void destroy_game(void *structure);
void destroy_sys(system_t *sys);
void destroy_menu(void *structure);
void destroy_setting(void *structure);
void free_draw_textbox(draw_textbox_t *draw, int stop);

#endif
