/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "wolf.h"

    #define HAND_POS WIN_WIDTH / 2 + 200
    #define PUNCH_POS WIN_WIDTH / 2 - 200
    #define MOV_OFFSET_GUN 4
    #define MAX_WIDTH 30

    #define FOV RAD(59)
    #define NUM_RAYS WIN_WIDTH
    #define RAY_LENGHT 2

    #define CEILING_COLOR sfColor_fromRGB(199, 199, 199)
    #define FLOOR_COLOR sfColor_fromRGB(139, 139, 139)
    #define TOOLBAR_COLOR sfColor_fromRGB(49, 49, 49)

    #define MAX_DISTANCE 100.0

    #define RENDER_DISTANCE 1200

    #define PLAYER_SPEED 100
    #define ROTATION_SPEED RAD(100)
    #define FORWARD_COEF 1.5

    #define DISTANCE_COLISION 5.0

    #define NB_DECIMAL_FLOAT_CMP 6

    #define SPRINT_COEF 1.1
    #define SPRINTING_FOV FOV * SPRINT_COEF
    #define TOOLBAR_HEIGHT 130
    #define TOOLBAR_POS (WIN_HEIGHT - TOOLBAR_HEIGHT)

    #define CROSSAIR_RADIUS 0.1

    #define HEAD_SPRITE_X 77
    #define HEAD_SPRITE_Y 90
    #define HEAD_SPRITE_STATUS 5

    #define OFFSET_POINT_BAR 20

    #define ARRAY_LENGHT(x) (sizeof(x) / sizeof(*x))

    #define OPEN_DISTANCE 96.0
    #define FINISH_DISTANCE 64.0

    #define AUTO_SAVE 30

typedef enum {
    LOAD_W_TEXTURE,
    LOAD_W_MUSIC,
    LOAD_W_POS_X,
    LOAD_W_POS_Y,
    LOAD_W_TILE,
    LOAD_W_SPEED,
    LOAD_W_RANGE,
    LOAD_W_KEY,
    NB_W_LOAD,
} load_weapon_info_t;

typedef enum wall_type {
    WALL,
    DESTRUCTIBLE,
    DOOR,
    FINAL,
} wall_type_t;

typedef struct int_wall_texture_s {
    int const value;
    char *const paths;
} int_wall_texture_t;

static const int_wall_texture_t wall_textures[] = {
    [WALL] = {1, "asset/wall.png"},
    [DESTRUCTIBLE] = {3, "asset/destructible.png"},
    [DOOR] = {2, "asset/door.png"},
    [FINAL] = {4, "asset/final.png"},
};

    #define NB_WALL_TXT ARRAY_LENGHT(wall_textures)

typedef enum intersection_type {
    NONE,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
} intersection_type_t;

typedef struct intersection_s {
    intersection_type_t type;
    wall_type_t wall;
} intersection_t;

typedef enum {
    TOOL_AMMO_NB,
    TOOL_AMMO_STR,
    TOOL_HEALTH_NB,
    TOOL_HEALTH_STR,
    TOOL_ARMOR_NB,
    TOOL_ARMOR_STR,
    TOOL_ONE,
    TOOL_TWO,
    TOOL_THREE,
    TOOL_FOUR,
    TOOL_ARM,
    TOOL_STAM_NB,
    TOOL_STAM_STR,
    TOOL_TIME_NB,
    TOOL_TIME_STR,
    TOOL_SCORE_NB,
    TOOL_SCORE_STR,
    TOOL_FPS,
    TOOL_SAVE,
    TOOL_INTERACT,
    NB_TOOLBAR,
} str_toolbar_t;

typedef enum {
    NO_WEAPON = -1,
    PUNCH,
    PISTOL,
    SHOTGUN,
    MINIGUN,
    NB_WEAPON,
} weapon_id_t;

typedef enum {
    DESTROY_WALL,
    DOOR_MU,
    END_LEVEL,
    FOOTSTEPP,
    NB_MUSIC,
} music_id_t;

typedef struct map_s {
    sfRectangleShape *ceiling_floor;
    sfVertexArray *lines[NB_WALL_TXT];
    sfRenderStates wall_states[NB_WALL_TXT];
} map_t;

typedef struct center_ray_s {
    sfVector2f v;
    sfVector2f pos;
    float distance;
    intersection_type_t type;
} center_ray_t;

typedef struct player_s {
    center_ray_t center_ray;
    sfVector2f pos;
    float angle;
    intersection_type_t type;
    float fov;
    sfBool is_sprinting;
    sfCircleShape *crossair;
    save_t *save;
} player_t;

typedef struct weapon_info_s {
    sfTexture *texture;
    sfVector2f posf;
    sfIntRect rectangle;
    sfMusic *sound;
    sfVector2f size;
    int current_tile;
    int nb_tile;
    double speed;
    float range;
    sfBool bag;
    int key;
} weapon_info_t;

typedef struct weapon_s {
    sfSprite *sprite;
    weapon_info_t *info;
    sfInt64 shot;
    sfMusic *empty;
    weapon_id_t weapon;
    double horizontal_offset;
} weapon_t;

typedef struct time_info_s {
    sfClock *clock;
    sfInt64 start_time;
    sfInt64 end_time;
    sfInt64 time;
    double delta;
} time_info_t;

typedef struct toolbar_s {
    sprite_t *head;
    draw_textbox_t *draw;
    sfRectangleShape *rectangle;
    sfTexture *background;
    sfBool fps;
    sfInt64 save;
    sfInt64 sprint;
    sfInt64 no_sprint;
    float last_save;
    sfBool saving;
    sfBool interact;
} toolbar_t;

typedef struct game_s {
    map_t *map;
    player_t *player;
    weapon_t *weapon;
    time_info_t *time_info;
    toolbar_t *tool;
    sfMusic *music[NB_MUSIC];
} game_t;

void cast_all_rays(game_t *game);
float cast_single_ray(player_t *player, float angle_offset,
    intersection_t *type, sfVector2f *intersection_point);
void move_player(
    player_t *player, double delta, int *head, sfMusic *footstepp);
int init_weapons(weapon_t *weapon);
void update_all(system_t *sys, game_t *game);
void update_time_end(time_info_t *time_info);
void update_save(system_t *sys, game_t *game);
void shot_gun_anim(
    weapon_t *weapon, time_info_t *time, toolbar_t *tool, int bag);

void game_events(system_t *sys, game_t *game);
void draw_game(system_t *sys, void *structure);
void destroy_game(void *structure);
void *init_game(void);

sfVector2i cast_pos(sfVector2f *pos, intersection_type_t type);

#endif
