/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** header
*/

#ifndef HEADER_H_
    #define HEADER_H_

    #define EXIT_S 0
    #define EXIT_F 84

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

    #define FOV ( M_PI / 3)
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

    #define PLAYER_SPEED 2.0
    #define ROTATION_SPPED RAD(3.0)
    #define FORWARD_COEF 2.0

    #define DISTANCE_COLISION 5.0

    #define TOOLBAR_POS (WIN_HEIGHT - 130)

typedef enum which_line {
    NONE,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
} which_line_t;

typedef enum {
    PUNCH,
    PISTOL,
    SHOTGUN,
} weapon_id_t;

typedef struct sprite_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f posf;
    sfVector2f scale;
    sfIntRect rectangle;
    int tile;
} sprite_t;

typedef struct weapon_s {
    sprite_t sprite;
    sfTexture **texture;
    sfMusic **sound;
    sfInt64 shot;
    int weapon;
} weapon_t;

typedef struct map_s {
    sfRectangleShape *ceiling_floor;
} map_t;

typedef struct player_s {
    sfVector2f pos;
    float angle;
    sfVector2f v;
    which_line_t type;
} player_t;

typedef struct game_s {
    sfRenderWindow *window;
    sfClock *clock;
    sfMusic *music;
    map_t *map;
    player_t *player;
    sfVertexArray *rays;
    sfBool fullscreen;
} game_t;

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

void init_player(player_t *player);
int init_game(game_t *game);
sfRenderWindow *create_window(sfUint32 style, double coeff);
int init_weapon(weapon_t *weapon);
void events(game_t *game, weapon_t *weapon);
void move_rect(sprite_t *sprite, int offset, int max_value);
void game_loop(game_t *game, weapon_t *weapon);
void init_map(map_t *map);
void cast_all_rays(game_t *game);
float cast_single_ray(player_t *player,
    float angle_offset, which_line_t *type);
void move_player(sfEvent event, player_t *player);
sfBool is_keyboard_input(sfEvent event, sfKeyCode key);

void destroy_weapon(weapon_t *weapon);
void destroy_game(game_t *game);

#endif
