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

    #define FOV RAD(59)
    #define NUM_RAYS WIN_WIDTH

    #define CEILING_COLOR sfColor_fromRGB(199, 199, 199)
    #define FLOOR_COLOR sfColor_fromRGB(149, 149, 149)
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

typedef enum intersection_type {
    NONE,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
} intersection_type_t;

typedef enum {
    TOOL_AMMO_NB,
    TOOL_AMMO_STR,
    TOOL_HEALTH_NB,
    TOOL_HEALTH_STR,
    TOOL_ONE,
    TOOL_TWO,
    TOOL_THREE,
    TOOL_FOUR,
    TOOL_ARM,
    TOOL_ARMOR_NB,
    TOOL_ARMOR_STR,
    TOOL_TIME_NB,
    TOOL_TIME_STR,
    TOOL_SCORE_NB,
    TOOL_SCORE_STR,
    TOOL_FPS,
    NB_TOOLBAR,
} str_toolbar_t;

typedef enum {
    PUNCH,
    PISTOL,
    SHOTGUN,
    MINIGUN,
    NB_WEAPON,
} weapon_id_t;

typedef struct map_s {
    sfRectangleShape *ceiling_floor;
    sfVertexArray *quads;
    sfRenderStates wall_state;
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
} weapon_info_t;

typedef struct weapon_s {
    sfSprite *sprite;
    weapon_info_t *info;
    sfInt64 shot;
    sfMusic *empty;
    weapon_id_t weapon;
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
} toolbar_t;

typedef struct game_s {
    map_t *map;
    player_t *player;
    weapon_t *weapon;
    time_info_t *time_info;
    toolbar_t *tool;
} game_t;

void cast_all_rays(game_t *game);
float cast_single_ray(player_t *player, float angle_offset,
    intersection_type_t *type, sfVector2f *intersection_point);
void move_player(player_t *player, double delta, int *head);
int init_weapons(weapon_t *weapon);
void update_all(system_t *sys, game_t *game);
void update_time_end(time_info_t *time_info);

void game_events(system_t *sys, game_t *game);
void draw_game(system_t *sys, void *structure);
void destroy_game(void *structure);
void *init_game(void);

sfVector2i cast_pos(sfVector2f *pos, intersection_type_t type);

#endif /* !GAME_H_ */
