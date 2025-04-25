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

    #define MAX_STRLEN 9
    #define MAX_NAME 25

    #define NB_SHOW_SAVE 3
    #define POS_OFFSET 20
    #define POS_COEFF 2.5

typedef struct linked_list_s linked_list_t;
typedef struct node_s node_t;

typedef struct save_s {
    char *name;
    sfVector2i size;
    sfVector2f start_pos;
    double start_angle;
    int **map;
    sfBool init;
    sfBool update;
} save_t;

typedef enum {
    NAME,
    SIZE_X,
    SIZE_Y,
    START_X,
    START_Y,
    START_ANGLE,
    MAP,
} str_t;

typedef struct file_s {
    char *path;
    char *name;
} file_t;

typedef enum str_normal_map_e {
    NOR_MAP_TITLE,
    NOR_MAP_SUB,
    NOR_MAP_SAVE1,
    NOR_MAP_SAVE2,
    NOR_MAP_SAVE3,
    NOR_MAP_BACK,
    NB_NOR_MAP,
} str_normal_map_t;

typedef struct info_save_s {
    int file;
    int nb_page;
    linked_list_t *list;
    node_t *current_file;
    sfBool update;
} info_save_t;

typedef struct normal_map_s {
    int str;
    draw_textbox_t *draw;
    info_save_t *info;
} normal_map_t;

typedef struct check_s {
    int (*check)(char *str);
} check_t;

int check_size(char *str);
int check_pos(char *str);
int check_angle(char *str);
int check_name(char *str);

static const check_t CHECK[] __maybe_unused = {
    [NAME] = {&check_name},
    [SIZE_X] = {&check_size},
    [SIZE_Y] = {&check_size},
    [START_X] = {&check_pos},
    [START_Y] = {&check_pos},
    [START_ANGLE] = {&check_angle},
    [MAP] = {NULL}
};

void free_map(int size, int **map);
int get_save(char *file, save_t *save);
int add_node_file(linked_list_t *list, char *file, char *dir);
void free_node_file(void *data);
linked_list_t *get_file(char *path);
void update_list(info_save_t *info, char *dir);
void draw_save(
    system_t *sys, info_save_t *info, draw_textbox_t *draw, int start);
bool sort_node_file(void *data_first, void *data_second);

void *init_normal_map(void);
void draw_normal_map(system_t *sys, void *structure);
void normal_map_events(system_t *sys, normal_map_t *normal_map);
void destroy_normal_map(void *structure);

#endif
