/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include "wolf.h"
    #include "linked_list.h"

    #define HAND_POS WIN_WIDTH / 2 + 200
    #define PUNCH_POS WIN_WIDTH / 2 - 200
    #define MOV_OFFSET_GUN 4
    #define MAX_WIDTH 30

    #define FOV RAD(60)
    #define RAY_LENGTH 2
    #define NB_RAYS WIN_WIDTH / RAY_LENGTH

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

    #define FLASHLIGHT_SPRITE_X (double)137 / 2
    #define FLASHLIGHT_SPRITE_Y 130
    #define FLASHLIGHT_SPRITE_STATUS 2
    #define FLASHLIGHT_COEF 0.28

    #define OFFSET_POINT_BAR 20

    #define ARRAY_LENGTH(x) (sizeof(x) / sizeof(*x))

    #define OPEN_DISTANCE 96.0
    #define FINISH_DISTANCE 64.0

    #define AUTO_SAVE 30

    #define MINI_MAP_SIZE 308
    #define MINI_MAP_NB_TILE 14
    #define MINI_MAP_TILE (MINI_MAP_SIZE / MINI_MAP_NB_TILE)
    #define MINI_MAP_OFFSET 7
    #define MINI_MAP_BORDER 25
    #define MINI_MAP_START ((MINI_MAP_TILE * -1) + MINI_MAP_BORDER)
    #define MINI_MAP_FOV 20
    #define MINI_MAP_CURSOR 5.0
    #define MINI_MAP_SHOW 4
    #define MINI_MAP_ROTATE 90
    #define MINI_MAP_RAY 3.0
    #define MINIOFF(pos) ((float)(pos % TILE_SIZE) * MINI_MAP_TILE / TILE_SIZE)

    #define OVERLAY_COLOR sfColor_fromRGBA(0, 0, 0, 200)
    #define FLASHLIGHT 300
    #define OVERLAY_STEP 10
    #define OVERLAY_MAX 200
    #define SMOOTH_OVERLAY 99

    #define WALL_TEXTURE_X 128.0
    #define WALL_TEXTURE_Y 128.0

    #define X_INDEX 0
    #define Y_INDEX 1

    #define LEN_INDEX 0
    #define FACTOR_INDEX 1

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
    int const text_offset_y;
} int_wall_texture_t;

static const int_wall_texture_t wall_textures[] = {
    [WALL] = {1, WALL_TEXTURE_Y * 0},
    [DESTRUCTIBLE] = {3, WALL_TEXTURE_Y * 1},
    [FINAL] = {4, WALL_TEXTURE_Y * 2},
    [DOOR] = {2, WALL_TEXTURE_Y * 3},
};

    #define NB_WALL_TXT ARRAY_LENGTH(wall_textures)

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
    int id;
} intersection_t;

typedef enum {
    TOOL_AMMO_NB,
    TOOL_AMMO_STR,
    TOOL_HEALTH_NB,
    TOOL_HEALTH_STR,
    TOOL_FLASH_NB,
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
    FOOTSTEPS,
    NB_MUSIC,
} music_id_t;

typedef struct light_s {
    sfRenderTexture *night_render;
    const sfTexture *night_texture;
    sfSprite *night;
    sfRectangleShape *overlay;
    sfCircleShape *flashlight;
    sfRenderStates state;
    sfBool flash_on;
    sfBool night_on;
    int sec;
} light_t;

typedef struct door_s {
    sfVector2i pos;
    float state;
    sfBool activated;
} door_t;

typedef struct ray_s {
    float len;
    sfVertex up;
    sfVertex down;
    int id;
} ray_t;

typedef struct map_s {
    sfRectangleShape *ceiling_floor;
    sfVertexArray *line;
    ray_t rays[WIN_WIDTH];
    sfRenderStates wall_states;
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
    sprite_t *flashlight;
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
    sfRectangleShape *mini_map;
    player_t *player;
    weapon_t *weapon;
    time_info_t *time_info;
    toolbar_t *tool;
    light_t *light;
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
void draw_minimap(
    system_t *sys, sfRectangleShape *mini_map, sfTexture *texture);
int init_toolbar(toolbar_t *tool);

void game_events(system_t *sys, game_t *game);
void draw_game(system_t *sys, void *structure);
void destroy_game(void *structure);
void *init_game(void);

float get_pourcentage_wall(intersection_type_t type, sfVector2f *intersection);
float get_door_pourcentage(save_t *save, sfVector2i *pos);
sfVector2i cast_pos(sfVector2f *pos, intersection_type_t type);
void center_ray(player_t *player);

#endif
