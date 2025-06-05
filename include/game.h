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
    #include "entities.h"

    #define HAND_POS WIN_WIDTH / 2 + 200
    #define PUNCH_POS WIN_WIDTH / 2 - 200
    #define MOV_OFFSET_GUN 4
    #define MAX_WIDTH 30

    #define FOV RAD(66)
    #define RAY_LENGTH 1
    #define NB_RAYS ((WIN_WIDTH / RAY_LENGTH) + 1)

    #define CEILING_COLOR sfColor_fromRGB(239, 239, 239)
    #define FLOOR_COLOR sfColor_fromRGB(139, 139, 139)
    #define TOOLBAR_COLOR sfColor_fromRGB(49, 49, 49)

    #define MAX_DISTANCE 100.0

    #define RENDER_DISTANCE 2000
    #define DISTANCE_ENEMY RENDER_DISTANCE

    #define PLAYER_SPEED 100
    #define ROTATION_SPEED RAD(100)
    #define FORWARD_COEF 1.5

    #define DISTANCE_COLISION 5.0

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

    #define TIME_OVERLAY 0.25
    #define WEPON_OVERLAY sfColor_fromRGBA(255, 255, 0, 50)
    #define ITEM_OVERLAY sfColor_fromRGBA(0, 255, 0, 50)
    #define SHOT_OVERLAY sfColor_fromRGBA(255, 0, 0, 100)

    #define MINI_MAP_SIZE 308
    #define MINI_MAP_NB_TILE 14
    #define MINI_MAP_TILE (float)(MINI_MAP_SIZE / MINI_MAP_NB_TILE)
    #define MINI_MAP_OFFSET 7
    #define MINI_MAP_BORDER 25
    #define MINI_MAP_START ((MINI_MAP_TILE * -1) + MINI_MAP_BORDER)
    #define MINI_MAP_FOV 3
    #define MINI_MAP_CURSOR 3
    #define MINI_MAP_SHOW 4
    #define MINI_MAP_ROTATE 90
    #define MINI_MAP_RAY 3.0
    #define MINIOFF(pos) ((float)(pos % TILE_SIZE) * MINI_MAP_TILE / TILE_SIZE)

    #define OVERLAY_COLOR sfColor_fromRGBA(0, 0, 0, 200)
    #define FLASHLIGHT 300
    #define NIGHT_NB 10
    #define OVERLAY_STEP (20 / NIGHT_NB)
    #define OVERLAY_MAX 200
    #define SMOOTH_OVERLAY (((MIN_IN_SEC - 10) * NIGHT_NB) - 1)

    #define WALL_TEXTURE_X 128.0
    #define WALL_TEXTURE_Y 128.0

    #define X_INDEX 0
    #define Y_INDEX 1

    #define LEN_INDEX 0
    #define FACTOR_INDEX 1

    #define Y_SPEED 750
    #define Y_MAX 500
    #define Y_MIN -Y_MAX

    #define NO_ENTITIE -1

    #define WEAPON_SCORE 10
    #define WALL_SCORE 5

    #define START_BLACK 500.0
    #define END_BLACK 1500.0
    #define MAX_COLOR 255

    #define UV_VALUE 75

    #define CROSS_HEAD_SIZE 5
    #define CROSS_HEAD_WIDTH 1.5

typedef enum {
    LOAD_W_TEXTURE,
    LOAD_W_MUSIC,
    LOAD_W_POS_X,
    LOAD_W_POS_Y,
    LOAD_W_TILE,
    LOAD_W_SPEED,
    LOAD_W_RANGE,
    LOAD_W_KEY,
    LOAD_W_DAMAGE,
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
    TOOL_BOSS,
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
    PICK_UP,
    HURT,
    BOSS_MUSIC,
    PLASMA_EXPLOSION,
    NB_MUSIC,
} music_id_t;

static const char *str_sound[] __maybe_unused = {
    [DESTROY_WALL] = "asset/destroy_wall.ogg",
    [DOOR_MU] = "asset/door.ogg",
    [END_LEVEL] = "asset/end_level.ogg",
    [FOOTSTEPS] = "asset/footsteps.ogg",
    [HURT] = "asset/hurt.ogg",
    [BOSS_MUSIC] = "asset/boss.ogg",
    [PICK_UP] = "asset/pick_up.ogg",
    [PLASMA_EXPLOSION] = "asset/plasma_explosion.ogg",
};

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
    sfVector2f posf;
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
} ray_t;

typedef struct map_s {
    sfRectangleShape *ceiling_floor;
    sfVertexArray *line;
    ray_t rays[NB_RAYS];
    sfRenderStates wall_states;
    int entity_center;
    sfBool is_wall;
    sfBool is_weakness;
    float timer_weakness;
} map_t;

typedef struct center_ray_s {
    sfVector2f pos;
    float distance;
    intersection_type_t type;
} center_ray_t;

typedef struct player_s {
    center_ray_t center_ray;
    sfVector2f pos;
    float angle;
    sfBool is_sprinting;
    sfCircleShape *crossair;
    sfConvexShape *headshot;
    save_t *save;
    float cam_angle;
    sfVector2f v;
    sfVector2f n;
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
    int damage;
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
    float shot;
    float item;
    float weapon;
    double delta;
} time_info_t;

typedef struct toolbar_s {
    sprite_t *head;
    sprite_t *flashlight;
    draw_textbox_t *draw;
    sfRectangleShape *rectangle;
    sfTexture *background;
    sfTexture *border;
    sfBool fps;
    sfInt64 save;
    sfInt64 sprint;
    sfInt64 no_sprint;
    float last_save;
    sfBool saving;
    sfBool interact;
    sfBool finish;
} toolbar_t;

typedef struct game_s {
    map_t *map;
    sfRectangleShape *mini_map;
    sfCircleShape *cursor;
    player_t *player;
    weapon_t *weapon;
    time_info_t *time_info;
    toolbar_t *tool;
    light_t *light;
    sfMusic *music[NB_MUSIC];
    sfRenderStates state_entities[NB_ENTITIES];
} game_t;

void cast_all_rays(game_t *game, save_t *save);
float cast_single_ray(player_t *player, float angle_offset,
    intersection_t *type, sfVector2f *intersection_point);
float cast_single_ray_enemy(player_t *player, float angle_offset,
    intersection_t *type, sfVector2f *intersection_point);
void move_player(game_t *game, double delta, int *head, sfMusic *footstepp);
int init_weapons(weapon_t *weapon);
void update_all(system_t *sys, game_t *game);
void update_time_end(time_info_t *time_info);
void update_save(system_t *sys, game_t *game);
void update_toolbar_percent(draw_textbox_t *draw, int nb);
void update_ammo(system_t *sys, game_t *game);
void shot_gun_anim(weapon_t *weapon,
    time_info_t *time, toolbar_t *tool, int bag);
void draw_minimap(system_t *sys, sfRectangleShape *mini_map,
    sfCircleShape *cursor, sfTexture *texture);
int init_toolbar(toolbar_t *tool);
int init_render_state(game_t *game);
void draw_minimap_entities(system_t *sys, linked_list_t *list,
    sfVector2i *player_tile, sfCircleShape *cursor);
void draw_square(
    system_t *sys, sfRectangleShape *mini_map, sfVector2i *player_tile);
void draw_center(system_t *sys, sfCircleShape *cursor);
void draw_look(system_t *sys, sfRectangleShape *mini_map);

void game_events(system_t *sys, game_t *game);

float get_pourcentage_wall(intersection_type_t type, sfVector2f *intersection);
float get_door_pourcentage(save_t *save, sfVector2i *pos);
sfVector2i cast_pos(sfVector2f *pos, intersection_type_t type);
void center_ray(game_t *game);
void sort_entities(game_t *game);
void enemies_movement(game_t *game, linked_list_t *enemies, save_t *save);
void move_y(player_t *player, double delta);
void draw_entities(game_t *game, system_t *sys);
void shot(system_t *sys, weapon_t *weapon, game_t *game);
sfBool get_next_pos(entity_t *enemy, game_t *game);
sfBool is_wall_between(game_t *game, entity_t *enemy);
sfColor get_color(float len);
void update_interact(toolbar_t *tool, player_t *player, int **map);
void show_game_environement(system_t *sys, game_t *game);
void add_node_boss(linked_list_t *boss, int health);
void draw_boss_health(system_t *sys, linked_list_t *boss,
    sfRectangleShape *rectangle, draw_textbox_t *draw);

#endif
