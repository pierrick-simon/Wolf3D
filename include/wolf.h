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
    #define WIN_BITS 64
    #define WIN_FRAME 60
    #define WIN_NAME "Wolf3D"

    #define SEC_IN_MICRO 1000000

    #define SHOTGUN_FRAME 0.05
    #define SHOTGUN_NB_TILE 5
    #define SHOTGUN_SPRITE_X 320
    #define SHOTGUN_SPRITE_Y 180

    #define TILE_SIZE 64
    #define MAP_WIDTH 15
    #define MAP_HEIGHT 15

    #define FOV ( M_PI / 3)
    #define NUM_RAYS 800

    #define CEILING_COLOR sfMagenta
    #define FLOOR_COLOR sfCyan

    #define DEG(rad) (180 / M_PI) * rad
    #define RAD(deg) (M_PI / 180) * deg

    #define MAX_DISTANCE 100.0

    #define RENDER_DISTANCE 1000

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
    sfColor ceiling_color;
    sfColor floor_color;
} map_t;

typedef struct player_s{
    float x;
    float y;
    float angle;
} player_t;

typedef struct game_s {
    sfRenderWindow *window;
    sfClock *clock;
    sfMusic *music;
    map_t *map;
    player_t *player;
} game_t;

static const int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0/*ici*/, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void init_player (player_t *player);
void init_game(game_t *game);
sfRenderWindow *create_window(void);
void init_weapon(weapon_t *weapon);
void events(game_t *game, weapon_t *weapon);
void move_rect(sprite_t *sprite, int offset, int max_value);
void game_loop(game_t *game, weapon_t *weapon);
void init_map(map_t *map);
void cast_all_rays(sfRenderWindow *window, player_t *player);
float cast_single_ray(player_t *player,
    float ray_angle, sfRenderWindow *window, float offest_x, float angle_offset, sfVertex *point);

typedef enum which_line {
    NONE,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
} which_line_t ;

#endif
