/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** save
*/

#ifndef SAVE_H_
    #define SAVE_H_

    #include "wolf.h"
    #include <stdbool.h>

    #define MAX_STRLEN 3
    #define MAX_NAME 15

    #define LEN_SAVE 13

    #define NB_SHOW_SAVE 3
    #define POS_OFFSET 20
    #define POS_COEFF 2.5

    #define SAVE_TIME 0.3

typedef struct linked_list_s linked_list_t;
typedef struct node_s node_t;

typedef enum item_info_e {
    INFO_HEALTH,
    INFO_AMMO_PISTOL,
    INFO_AMMO_SHUTGUN,
    INFO_AMMO_MINIGUN,
    INFO_AMMO_PLASMA,
    INFO_STAMINA,
    INFO_FLASHLIGHT,
    NB_INFO,
} item_info_t;

typedef struct player_info_s {
    sfVector2f start_pos;
    double start_angle;
    float item_info[NB_INFO];
    int score;
    sfUint64 time;
    int weapons;
    int start_weapon;
    float difficulty;
} player_info_t;

typedef struct save_s {
    char *name;
    sfVector2i size;
    sfMusic *music;
    char *music_path;
    int **map;
    sfColor **mini_map;
    sfBool init;
    sfBool update;
    player_info_t *info;
    linked_list_t *doors;
    linked_list_t *entities;
    linked_list_t *boss;
} save_t;

typedef enum {
    NAME,
    SIZE_X,
    SIZE_Y,
    START_X,
    START_Y,
    START_ANGLE,
    HEALTH,
    FLASHLIGHT_INFO,
    AMMO_PISTOL,
    AMMO_SHUTGUN,
    AMMO_MINIGUN,
    AMMO_PLASMA,
    STAMINA,
    CURRENT_SCORE,
    TIME,
    WEAPONS,
    START_WEAPON,
    DIFFICULTY_INFO,
    MUSIC,
    ENTITIES,
    COOR,
} str_t;

typedef struct file_s {
    char *path;
    char *name;
} file_t;

typedef enum str_levels_e {
    LEVELS_TITLE,
    LEVELS_SUB,
    LEVELS_SAVE1,
    LEVELS_SAVE2,
    LEVELS_SAVE3,
    LEVELS_BACK,
    NB_LEVELS,
} str_levels_t;

typedef enum str_map_e {
    MAP_TITLE,
    MAP_PLAY,
    MAP_CONTINUE,
    MAP_SCORE,
    MAP_EDIT,
    MAP_BACK,
    NB_MAP,
} str_map_t;

typedef struct info_save_s {
    int file;
    int nb_page;
    linked_list_t *list;
    node_t *current_file;
    sfBool update;
} info_save_t;

typedef struct levels_s {
    int str;
    draw_textbox_t *draw;
    info_save_t *info;
} levels_t;

typedef struct select_map_s {
    int str;
    draw_textbox_t *draw;
    sfBool save;
    sfBool check;
    sfBool edit;
} select_map_t;

typedef struct check_s {
    int (*check)(char *str);
} check_t;

int check_size(char *str);
int check_pos(char *str);
int check_angle(char *str);
int check_name(char *str);
int check_info(char *str);

static const check_t CHECK[] __maybe_unused = {
    [NAME] = {&check_name},
    [SIZE_X] = {&check_size},
    [SIZE_Y] = {&check_size},
    [START_X] = {&check_pos},
    [START_Y] = {&check_pos},
    [START_ANGLE] = {&check_angle},
    [HEALTH] = {&check_info},
    [FLASHLIGHT_INFO] = {&check_info},
    [AMMO_PISTOL] = {&check_info},
    [AMMO_SHUTGUN] = {&check_info},
    [AMMO_MINIGUN] = {&check_info},
    [AMMO_PLASMA] = {&check_info},
    [STAMINA] = {&check_info},
    [CURRENT_SCORE] = {&check_info},
    [TIME] = {&check_info},
    [WEAPONS] = {&check_info},
    [START_WEAPON] = {&check_info},
    [DIFFICULTY_INFO] = {&check_angle},
    [COOR] = {NULL}
};

void destroy_save(save_t *save);
void free_map(int size, int **map);
int get_save(char *file, save_t *save);
int add_node_file(linked_list_t *list, char *file, char *dir);
void free_node_file(void *data);
linked_list_t *get_file(char *path);
void update_list(info_save_t *info, char *dir);
void draw_save(
    system_t *sys, info_save_t *info, draw_textbox_t *draw, int start);
bool sort_node_file(void *data_first, void *data_second);
void save_score(save_t *save, char *name);
void save_map(save_t *save, char *dir);
void free_mini_map_color(sfColor **color, int y);
int init_mini_map_color(save_t *save);
int add_node_entity(linked_list_t *enemies, char *line);
int check_start(save_t *save);
int check_save(save_t *save, char **tab, int *offset);

void levels_events(system_t *sys, levels_t *levels);
void your_maps_events(system_t *sys, levels_t *levels);
void map_events(system_t *sys, select_map_t *map);

#endif
