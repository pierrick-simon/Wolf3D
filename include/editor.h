/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** editor
*/

#ifndef EDITOR_H_
    #define EDITOR_H_

    #include "wolf.h"
    #include "save.h"

    #define EDIT_BACKGROUND sfColor_fromRGB(200, 200, 200)

    #define ANGLE_X RAD(0.0)
    #define ANGLE_Y RAD(35.0)

    #define MARGIN 150

    #define ZOOM 0.1
    #define MAX_ZOOM 5.0
    #define MIN_ZOOM 0.5

    #define MOVE 5

    #define SIZE_X_BUTTON 115.00
    #define SIZE_Y_BUTTON 60.00
    #define SIZE_TEXT_BUTTON 27

typedef struct linked_list_s linked_list_t;
typedef struct node_s node_t;

typedef enum {
    EDIT_NONE,
    EDIT_WALL,
    EDIT_DOOR,
    EDIT_DESTRUCTIBLE,
    EDIT_END,
    EDIT_START,
    EDIT_SMALL_HEALTH,
    EDIT_BIG_HEALTH,
    EDIT_STAMINA,
    EDIT_AMMO_PISTOL,
    EDIT_AMMO_SHUTGUN,
    EDIT_AMMO_MINIGUN,
    EDIT_FLASHLIGHT,
    EDIT_WEAPON_TWO,
    EDIT_WEAPON_THREE,
    EDIT_WEAPON_FOUR,
    EDIT_SWORD_ENEMY,
    EDIT_GUN_ENEMY,
    EDIT_SHEET_ENEMY,
    EDIT_CYBORG,
    EDIT_GROWLER,
    EDIT_PHANTOM,
    EDIT_BOSS,
    EDIT_CENTER,
    EDIT_RESET,
    EDIT_REFRESH,
    EDIT_PREV,
    EDIT_NEXT,
    EDIT_GENERATE,
    NB_EDIT,
} edit_t;

typedef enum str_edit_info_e {
    EDIT_INF_TITLE,
    EDIT_INF_NAME,
    EDIT_INF_X,
    EDIT_INF_Y,
    EDIT_INF_BACK,
    NB_EDIT_INF,
} str_edit_info_t;

typedef enum str_edit_map_e {
    EDIT_MAP_TITLE,
    EDIT_MAP_TOOLS,
    EDIT_MAP_TILE,
    EDIT_MAP_ENEMY,
    EDIT_MAP_ITEM,
    EDIT_MAP_SAVE,
    EDIT_MAP_BACK,
    NB_EDIT_MAP,
} str_edit_map_t;

typedef struct edit_info_s {
    str_edit_info_t str;
    draw_textbox_t *draw;
    char string[NB_EDIT_INF][MAX_NAME + 1];
    char str_tmp[NB_EDIT_INF][MAX_NAME + 1];
} edit_info_t;

typedef struct draw_map_s {
    int **map;
    sfVector2f **coor;
    sfVector2i size;
    sfVector2f pos;
    float rotate;
    float zoom;
    float coef;
    sfConvexShape *shape;
} draw_map_t;

typedef struct buttons_s {
    sfFloatRect bounds[NB_EDIT];
    sfBool hover[NB_EDIT];
    sfRectangleShape *rectangle;
    sfBool press;
} buttons_t;

typedef struct edit_map_s {
    draw_textbox_t *draw;
    str_edit_map_t str;
    edit_t edit;
    sfColor color[NB_EDIT];
    buttons_t *buttons;
    draw_map_t *draw_map;
    sfBool update;
    linked_list_t *history;
    node_t *current;
} edit_map_t;

typedef enum {
    STAY,
    CLICK,
} button_state_t;

typedef struct history_s {
    int **map;
    int size;
} history_t;

typedef struct button_s {
    sfVector2f pos;
    char *text;
    button_state_t state;
    void (*f)(system_t *sys, edit_map_t *edit);
} button_t;

typedef struct generate_s {
    sfVector2i room;
    sfVector2i wall_horizontal;
    sfVector2i wall_vertical;
    int room_map[52][52];
    int map_horizontal[52][52];
    int map_vertical[52][52];
} generate_t;

void reset_button(system_t *sys, edit_map_t *edit);
void center_button(system_t *sys, edit_map_t *edit);
void refresh_button(system_t *sys, edit_map_t *edit);
void prev_button(system_t *sys, edit_map_t *edit);
void next_button(system_t *sys, edit_map_t *edit);
void generate_map(system_t *sys, edit_map_t *edit);

static const button_t BUTTON[] __maybe_unused = {
    [EDIT_NONE] = {(sfVector2f){55, 640}, "none", STAY},
    [EDIT_WALL] = {(sfVector2f){205, 640}, "wall", STAY},
    [EDIT_DESTRUCTIBLE] = {(sfVector2f){55, 730}, "destrucitble", STAY},
    [EDIT_DOOR] = {(sfVector2f){205, 730}, "door", STAY},
    [EDIT_END] = {(sfVector2f){55, 820}, "end", STAY},
    [EDIT_START] = {(sfVector2f){205, 820}, "start", STAY},
    [EDIT_SMALL_HEALTH] = {(sfVector2f){1600, 640}, "small health", STAY},
    [EDIT_BIG_HEALTH] = {(sfVector2f){1750, 640}, "big health", STAY},
    [EDIT_STAMINA] = {(sfVector2f){1600, 730}, "staminat", STAY},
    [EDIT_AMMO_PISTOL] = {(sfVector2f){1750, 730}, "ammo pistol", STAY},
    [EDIT_AMMO_SHUTGUN] = {(sfVector2f){1600, 820}, "ammo shutgun", STAY},
    [EDIT_AMMO_MINIGUN] = {(sfVector2f){1750, 820}, "ammo minigun", STAY},
    [EDIT_FLASHLIGHT] = {(sfVector2f){1600, 910}, "flashlight", STAY},
    [EDIT_WEAPON_TWO] = {(sfVector2f){1750, 910}, "pistol", STAY},
    [EDIT_WEAPON_THREE] = {(sfVector2f){1600, 1000}, "shutgun", STAY},
    [EDIT_WEAPON_FOUR] = {(sfVector2f){1750, 1000}, "minigun", STAY},
    [EDIT_SWORD_ENEMY] = {(sfVector2f){1600, 160}, "sword", STAY},
    [EDIT_GUN_ENEMY] = {(sfVector2f){1750, 160}, "gun", STAY},
    [EDIT_SHEET_ENEMY] = {(sfVector2f){1600, 250}, "sheet", STAY},
    [EDIT_CYBORG] = {(sfVector2f){1750, 250}, "cyborg", STAY},
    [EDIT_GROWLER] = {(sfVector2f){1600, 340}, "growler", STAY},
    [EDIT_PHANTOM] = {(sfVector2f){1750, 340}, "phantom", STAY},
    [EDIT_BOSS] = {(sfVector2f){1675, 430}, "boss", STAY},
    [EDIT_RESET] = {(sfVector2f){55, 250}, "reset", CLICK, &reset_button},
    [EDIT_REFRESH] = {(sfVector2f){205, 250},
        "refresh", CLICK, &refresh_button},
    [EDIT_PREV] = {(sfVector2f){55, 160}, "prev", CLICK, &prev_button},
    [EDIT_NEXT] = {(sfVector2f){205, 160}, "next", CLICK, &next_button},
    [EDIT_CENTER] = {(sfVector2f){55, 340}, "center", CLICK, &center_button},
    [EDIT_GENERATE] = {(sfVector2f){205, 340},
        "generate", CLICK, &generate_map},
};

void edit_info_events(system_t *sys, edit_info_t *edit_info);
void edit_map_events(system_t *sys, edit_map_t *edit_map);
void map_event(sfEvent event, edit_map_t *edit_map);

void free_2d_map(sfVector2i size, sfVector2f **map);
sfVector2f **create_2d_map(draw_map_t *edit);
sfVector2i which_tile(system_t *sys, draw_map_t *edit, sfVector2f **map);
void draw_button(system_t *sys, buttons_t *buttons, edit_map_t *edit);
void add_node_history(edit_map_t *edit);
void free_node_history(void *data);
void del_head_history(edit_map_t *edit);
void mouse_click(system_t *sys, edit_map_t *edit, sfVector2f **map);
sfBool replace_nb_room(generate_t *generate, int one, int two);
int count_wall(generate_t *generate);
sfVector2i get_n_wall_pos(generate_t *generate, int n, sfBool *vertical);
void generate_room(system_t *sys, edit_map_t *edit, generate_t *generate);

#endif /* !EDITOR_H_ */
