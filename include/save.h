/*
** EPITECH PROJECT, 2025
** Wolf3d
** File description:
** save
*/

#ifndef SAVE_H_
    #define SAVE_H_

    #include "wolf.h"

    #define MAX_STRLEN 9
    #define MAX_NAME 25

typedef struct save_s {
    char *name;
    sfVector2i size;
    sfVector2f start_pos;
    double start_angle;
    int **map;
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

#endif
